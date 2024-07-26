local WallJumpState = {}

Script:property("wallJumpTime", 200)

function WallJumpState:new(stateMachine, movement, animations, playAnimation, input)
    local obj = {}
    setmetatable(obj, self)
    self.__index = self
    self.stateMachine = stateMachine
    self.movement = movement
    self.animations = animations
    self.playAnimation = playAnimation
    self.input = input
    return obj
end

function WallJumpState:controlAnimations()
    if self.movement.verticalSpeed < 0 then
        self.playAnimation(self.animations.jump)
    else
        self.playAnimation(self.animations.fall)
    end
end

function WallJumpState:enter()
    self.startTime = Time:getTime()
    self.movement:flipHorizontalInput()
    self.movement:setJumpInput(false)
    self.movement:moveMaxSpeed()
end

function WallJumpState:exit()

end

function WallJumpState:update()
    self.movement:move()
    self.movement:calculateGravity()
    self.movement:jump()

    self:controlAnimations()
    if self.startTime + dashTime < Time:getTime() or self.movement.isGrounded then
        self.stateMachine:changeState(self.stateMachine.states.moveState)
    end
end

return WallJumpState