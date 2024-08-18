local Helper_Functions = require("HelperFunctions")

local Movement = {}

function Movement.registerProperties(tableComponent)
    -- move
    tableComponent.accelerationTime = 0.3
    tableComponent.deccelerationTime = 0.2
    tableComponent.maxSpeed = 80
    -- climb
    --script:property("climbSpeed", 40)
    -- wall slide
    --script:property("wallSideMaxFallSpeed", 10)
    -- jump
    tableComponent.jumpDist         = 3   * 16
    tableComponent.jumpHeight       = 4.5 * 16
    tableComponent.jumpArcHeight    = 1   * 16
    tableComponent.jumpArcDist      = 1   * 16
    tableComponent.jumpFallDist     = 2   * 16
    tableComponent.maxFallSpeed     = 130
    tableComponent.bufferTime = 100
    tableComponent.coyoteTime = 100
    -- collision
    --script:property("groundCheckArea", 1)
    --script:property("groundLayer", 1)
    --script:property("groundAngle", 25)
    -- dash
    --script:property("dashSpeed", 500)
end

function Movement:new()
    local obj = {}
    setmetatable(obj, self)
    self.__index = self
    --input
    obj.horizontalInput = 0
    obj.verticalInput = 0
    obj.jumpInput = false
    obj.jumpInputUsed = true
    obj.lastJumpPress = 0
    --move
    obj.horizontalSpeed = 0
    obj.curAcceleration = 0
    obj.facing = 1
    --jump
    obj.isGrounded = false
    obj.verticalSpeed = 0
    obj.endJumpEarly = false
    obj.timeLeftGrounded  = 0
    obj.jumping = false
    obj.coyoteUsable = false
    -- these are for animation controls
    obj.justJumped = false
    obj.justLanded = false
    obj.justInAir = false
    --dash
    obj.canDash = false
    obj.isDashing = false
    return obj
end

--------------------------------------------------------------
--INPUT
--------------------------------------------------------------
function Movement:setVerticalInput(value)
    self.verticalInput = value
end

function Movement:setHorizontalInput(value)
    self.horizontalInput = value
    if value ~= 0 then
        self.facing = value
    end
end

function Movement:flipHorizontalInput()
    self.horizontalInput = -self.facing
    self.facing = self.horizontalInput
end

function Movement:setJumpInput(value, systemTime)
    if value then
        self.lastJumpPress = systemTime
        if value ~= self.jumpInput then
            self.jumpInputUsed = false
        end
    end
    self.jumpInput = value
end

--------------------------------------------------------------
--MOVE
--------------------------------------------------------------
function Movement:moveMaxSpeed(tableComponent)
    self.horizontalSpeed = self.horizontalInput * tableComponent.maxSpeed
end

function Movement:move(tableComponent, systemTime, dt)
    self.curAcceleration = self.horizontalSpeed / tableComponent.maxSpeed
    local stillDeccelerating = self.horizontalInput * self.curAcceleration < 0
    if self.horizontalInput ~= 0 and (not stillDeccelerating or tableComponent.accelerationTime < tableComponent.deccelerationTime) then
        --acceleration
        local deltaAcceleration = tableComponent.accelerationTime <= 0 and self.horizontalInput or (self.horizontalInput * dt / tableComponent.accelerationTime)
        self.curAcceleration = self.curAcceleration + deltaAcceleration
        self.curAcceleration = Helper_Functions.Clamp(self.curAcceleration, -1, 1)
    else
        --decceleration
        local deltaAcceleration = tableComponent.deccelerationTime <= 0 and 1 or (dt / tableComponent.deccelerationTime)
        self.curAcceleration = Helper_Functions.MoveTowards(self.curAcceleration, 0, deltaAcceleration)
    end
    self.horizontalSpeed = self.curAcceleration * tableComponent.maxSpeed
end

--------------------------------------------------------------
--CLIMB
--------------------------------------------------------------
function Movement:climb()
    self.verticalSpeed = self.verticalInput * climbSpeed
end

--------------------------------------------------------------
--WALLSLIDE
--------------------------------------------------------------
Movement.isWallSliding = false

function Movement:wallSlide()
    self.isGrounded = self.checkGrounded() -- TODO Improve grounded check so it is not being checked in multiple functions
    
    local deltaSpeed = self:fallGravity() * Time:getDeltaTime()
    self.verticalSpeed = self.verticalSpeed + deltaSpeed

    -- clamp speed
    if self.verticalSpeed > wallSideMaxFallSpeed then
        self.verticalSpeed = wallSideMaxFallSpeed
    end
end

--------------------------------------------------------------
--JUMP
--------------------------------------------------------------
function Movement:canUseCoyote(tableComponent, systemTime)
    return self.coyoteUsable and not self.isGrounded and (self.timeLeftGrounded + tableComponent.coyoteTime > systemTime) and self.lastJumpPress == systemTime
end

function Movement:hasBufferJump(tableComponent, systemTime)
    return self.isGrounded and (self.lastJumpPress + tableComponent.bufferTime > systemTime)
end

function Movement:hasWallJump(tableComponent, systemTime)
    return self.isWallSliding and self.lastJumpPress == systemTime
end

function Movement:jumpSpeed(tableComponent, systemTime)
    return tableComponent.jumpDist ~= 0 and (2 * tableComponent.jumpHeight * tableComponent.maxSpeed) / tableComponent.jumpDist or 0
end

function Movement:jumpArcSpeed(tableComponent, systemTime)
    return tableComponent.jumpArcDist ~= 0 and (2 * tableComponent.jumpArcHeight * tableComponent.maxSpeed) / tableComponent.jumpArcDist or 0
end

function Movement:jumpGravity(tableComponent, systemTime)
    return tableComponent.jumpDist ~= 0 and (2 * tableComponent.jumpHeight * tableComponent.maxSpeed  ^ 2) / tableComponent.jumpDist ^ 2 or 0
end

function Movement:jumpArcGravity(tableComponent, systemTime)
    return tableComponent.jumpArcDist ~= 0 and (2 * tableComponent.jumpArcHeight * tableComponent.maxSpeed ^ 2) / tableComponent.jumpArcDist ^ 2 or 0
end

function Movement:fallGravity(tableComponent, systemTime)
    return tableComponent.jumpFallDist ~= 0 and (2 * tableComponent.jumpHeight * tableComponent.maxSpeed ^ 2) / tableComponent.jumpFallDist * 2 or 0
end

function Movement:calculateGravity(tableComponent, systemTime, dt, isGrounded)
    self.justLanded = false
    self.justInAir = false
    if self.isGrounded ~= isGrounded then
        self.isGrounded = isGrounded
        if self.isGrounded then
            self.coyoteUsable = true
            self.justLanded = true
            self.jumping = false
        else
            self.timeLeftGrounded = systemTime
            if not self.jumping then
                self.justInAir = true
            end
        end
    end
    if not self.isGrounded then 
        local deltaSpeed = (self.verticalSpeed < 0 and (self.endJumpEarly and self:jumpArcGravity(tableComponent, systemTime) or self:jumpGravity(tableComponent, systemTime)) or self:fallGravity(tableComponent, systemTime)) * dt
        self.verticalSpeed = self.verticalSpeed + deltaSpeed

        -- clamp speed
        if self.verticalSpeed > tableComponent.maxFallSpeed then 
            self.verticalSpeed = tableComponent.maxFallSpeed
        end
    end
end

function Movement:jump(tableComponent, systemTime, dt)
    -- can jump if: grounded or within coyote threshold or sufficient jump buffer
    if not self.jumpInputUsed and (self:hasBufferJump(tableComponent, systemTime) or self:canUseCoyote(tableComponent, systemTime) or self:hasWallJump(tableComponent, systemTime)) then 
        self.verticalSpeed = -self:jumpSpeed(tableComponent, systemTime)
        self.jumpInputUsed = true
        self.endJumpEarly = false
        self.coyoteUsable = false
        self.justJumped = true
        self.jumping = true
    else
        self.justJumped = false
    end
    -- end jump input once at jump arc
    if self.verticalSpeed > -self:jumpArcSpeed(tableComponent, systemTime) then
        self.endJumpEarly = true
    end
    -- test to end jump early
    --if not self.isGrounded and not self.jumpInput and not self.endJumpEarly then
    --    self.endJumpEarly = true
    --    self.verticalSpeed = -self:jumpArcSpeed(tableComponent, systemTime)
    --end
end

--------------------------------------------------------------
--DASH
--------------------------------------------------------------
function Movement:dash()
    self.canDash = false
    self.horizontalSpeed = self.facing * dashSpeed
    self.verticalSpeed = 0
end

--------------------------------------------------------------
--HELPER
--------------------------------------------------------------
function Movement:setSpeed(velocity)
    self.horizontalSpeed = velocity.x
    self.verticalSpeed = velocity.y
end

function Movement:setHorizontalSpeed(x)
    self.horizontalSpeed = x
end

function Movement:setVerticalSpeed(y)
    self.verticalSpeed = y
end

function Movement:getSpeed()
    return self.horizontalSpeed, self.verticalSpeed
end

return Movement