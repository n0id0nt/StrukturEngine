local Helper_Functions = require("HelperFunctions")

local Movement = {}

function Movement.registerProperties(script)
    -- move
    script:property("accelerationTime", 0.3)
    script:property("deccelerationTime", 0.2)
    script:property("maxSpeed", 80)
    -- climb
    script:property("climbSpeed", 40)
    -- wall slide
    script:property("wallSideMaxFallSpeed", 10)
    -- jump
    script:property("jumpDist", 16 * 3)
    script:property("jumpHeight", 16 * 6)
    script:property("jumpArcHeight", 16)
    script:property("jumpArcDist", 16)
    script:property("jumpFallDist", 16 * 2)
    script:property("maxFallSpeed", 300)
    script:property("bufferTime", 100)
    script:property("coyoteTime", 100)
    -- collision
    script:property("groundCheckArea", 1)
    script:property("groundLayer", 1)
    script:property("groundAngle", 25)
    -- dash
    script:property("dashSpeed", 500)
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

function Movement:setJumpInput(value)
    if value then
        self.lastJumpPress = Time:getTime()
        if value ~= self.jumpInput then
            self.jumpInputUsed = false
        end
    end
    self.jumpInput = value
end

--------------------------------------------------------------
--MOVE
--------------------------------------------------------------
function Movement:moveMaxSpeed()
    self.horizontalSpeed = self.horizontalInput * maxSpeed
end

function Movement:move()
    self.curAcceleration = self.horizontalSpeed / maxSpeed
    local stillDeccelerating = self.horizontalInput * self.curAcceleration < 0
    if self.horizontalInput ~= 0 and (not stillDeccelerating or accelerationTime < deccelerationTime) then
        --acceleration
        local deltaAcceleration = accelerationTime <= 0 and self.horizontalInput or (self.horizontalInput * Time:getDeltaTime() / accelerationTime)
        self.curAcceleration = self.curAcceleration + deltaAcceleration
        self.curAcceleration = Helper_Functions.Clamp(self.curAcceleration, -1, 1)
    else
        --decceleration
        local deltaAcceleration = deccelerationTime <= 0 and 1 or (Time:getDeltaTime() / deccelerationTime)
        self.curAcceleration = Helper_Functions.MoveTowards(self.curAcceleration, 0, deltaAcceleration)
    end
    self.horizontalSpeed = self.curAcceleration * maxSpeed
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
function Movement:canUseCoyote()
    return self.coyoteUsable and not self.isGrounded and (self.timeLeftGrounded + coyoteTime > Time:getTime()) and self.lastJumpPress == Time:getTime()
end

function Movement:hasBufferJump()
    return self.isGrounded and (self.lastJumpPress + bufferTime > Time:getTime())
end

function Movement:hasWallJump()
    return self.isWallSliding and self.lastJumpPress == Time:getTime()
end

function Movement:jumpSpeed()
    return jumpDist ~= 0 and (2 * jumpHeight * maxSpeed) / jumpDist or 0
end

function Movement:jumpArcSpeed()
    return jumpArcDist ~= 0 and (2 * jumpArcHeight * maxSpeed) / jumpArcDist or 0
end

function Movement:jumpGravity()
    return jumpDist ~= 0 and (2 * jumpHeight * maxSpeed ^ 2) / jumpDist ^ 2 or 0
end

function Movement:jumpArcGravity()
    return jumpArcDist ~= 0 and (2 * jumpArcHeight * maxSpeed ^ 2) / jumpArcDist ^ 2 or 0
end

function Movement:fallGravity()
    return jumpFallDist ~= 0 and (2 * jumpHeight * maxSpeed ^ 2) / jumpFallDist * 2 or 0
end

function Movement:calculateGravity()
    local newIsGrounded = self:checkGrounded()
    self.justLanded = false
    self.justInAir = false
    if self.isGrounded ~= newIsGrounded then
        self.isGrounded = newIsGrounded
        if self.isGrounded then
            self.coyoteUsable = true
            self.justLanded = true
            self.jumping = false
        else
            self.timeLeftGrounded = Time:getTime()
            if not self.jumping then
                self.justInAir = true
            end
        end
    end
    if not self.isGrounded then 
        local deltaSpeed = (self.verticalSpeed < 0 and (self.endJumpEarly and self:jumpArcGravity() or self:jumpGravity()) or self:fallGravity()) * Time:getDeltaTime()
        self.verticalSpeed = self.verticalSpeed + deltaSpeed

        -- clamp speed
        if self.verticalSpeed > maxFallSpeed then 
            self.verticalSpeed = maxFallSpeed
        end
    end
end

function Movement:jump()
    -- can jump if: grounded or within coyote threshold or sufficient jump buffer
    if not self.jumpInputUsed and (self:hasBufferJump() or self:canUseCoyote() or self:hasWallJump()) then 
        self.verticalSpeed = -self:jumpSpeed()
        self.jumpInputUsed = true
        self.endJumpEarly = false
        self.coyoteUsable = false
        self.justJumped = true
        self.jumping = true
    else
        self.justJumped = false
    end
    -- end jump input once at jump arc
    if self.verticalSpeed > -self:jumpArcSpeed() then
        self.endJumpEarly = true
    end
    -- test to end jump early
    if not self.isGrounded and not self.jumpInput and not self.endJumpEarly then
        self.endJumpEarly = true
        self.verticalSpeed = -self:jumpArcSpeed()
    end
end

--------------------------------------------------------------
--COLLISION
--------------------------------------------------------------
function Movement:checkGrounded()
    return GO:getPhysicsBody():checkGrounded(groundAngle)
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
function Movement:setSpeed(x, y)
    self.horizontalSpeed = x
    self.verticalSpeed = y
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