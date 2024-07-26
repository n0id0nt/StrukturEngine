local MoveState = {}

function MoveState:new(stateMachine, movement, animations, playAnimation, input, params)
    local obj = {}
    setmetatable(obj, self)
    self.__index = self
    self.stateMachine = stateMachine
    self.movement = movement
    self.animations = animations
    self.playAnimation = playAnimation
    self.input = input
    self.params = params
    return obj
end

function MoveState:controlAnimations()
    if self.movement.isGrounded then
        if self.movement.horizontalInput ~= 0 then
            self.playAnimation(self.animations.run)
        else
            self.playAnimation(self.animations.idle)
        end
    else
        if self.movement.verticalSpeed < 0 then
            self.playAnimation(self.animations.jump)
        else
            self.playAnimation(self.animations.fall)
        end
    end
end

function MoveState:enter()

end

function MoveState:exit()

end

function MoveState:update()
    self.movement:setHorizontalInput(self.input.horizontalInput)
    if self.input.horizontalInput ~= 0 then
        GO:getSprite().flipped = self.input.horizontalInput < 0
    end
    self.movement:setJumpInput(self.input.jumpInput)

    self.movement:move()
    self.movement:calculateGravity()
    self.movement:jump()

    self:controlAnimations()

    if Input:isInputDown("Dash") then
        self.stateMachine:changeState(self.stateMachine.states.dashState)
    elseif Input:isInputDown("Grab") and self.params.ladder > 0 then
        self.stateMachine:changeState(self.stateMachine.states.climbState)
    elseif not self.movement.isGrounded and self.movement.verticalSpeed > 0 and self.movement.horizontalInput ~= 0 and GO:getPhysicsBody():checkCollisionAtAngle(self.movement.horizontalInput > 0 and 0 or 180, groundAngle) then
        self.stateMachine:changeState(self.stateMachine.states.wallSlideState)
    end
end

return MoveState