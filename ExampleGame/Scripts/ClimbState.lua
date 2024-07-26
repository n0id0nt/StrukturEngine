local ClimbState = {}

function ClimbState:new(stateMachine, movement, animations, playAnimation, input, params)
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

function ClimbState:enter()
    GO:getSpriteAnimation():playAnimation(self.animations.climb)
    self.movement:setHorizontalSpeed(0)
end

function ClimbState:exit()

end

function ClimbState:update()

    self.movement:setVerticalInput(self.input.verticalInput)
    self.movement:climb()

    if Input:isInputJustReleased("Grab") or self.params.ladder == 0 then
        self.stateMachine:changeState(self.stateMachine.states.moveState)
    end
end

return ClimbState