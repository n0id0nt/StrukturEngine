local WallSlideState = {}

function WallSlideState:new(stateMachine, movement, animations, playAnimation, input)
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

function WallSlideState:enter()
    GO:getSpriteAnimation():playAnimation(self.animations.wallSlide)
    self.movement.isWallSliding = true
end

function WallSlideState:exit()
    self.movement.isWallSliding = false
end

function WallSlideState:update()
    self.movement:wallSlide()

    if self.movement.isGrounded or not GO:getPhysicsBody():checkCollisionAtAngle(self.movement.horizontalInput > 0 and 0 or 180, groundAngle) then
        self.stateMachine:changeState(self.stateMachine.states.moveState)
    elseif Input:isInputJustPressed("Jump") then
        self.movement:setJumpInput(true) -- Don't like this should be doeing this in enter function of wall jump state but not wall sliding then
        self.movement:jump()
        self.stateMachine:changeState(self.stateMachine.states.wallJumpState)
    end
end

return WallSlideState