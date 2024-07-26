local DashState = {}

Script:property("dashTime", 500)

function DashState:new(stateMachine, movement, animations, playAnimation, input)
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

function DashState:enter()
    GO:getSpriteAnimation():playAnimation(self.animations.dash)
    self.startTime = Time:getTime()
    GO:getCamera():addShakeTrauma(0.5)
end

function DashState:exit()

end

function DashState:update()
    self.movement:dash()

    if self.startTime + dashTime < Time:getTime() then
        self.stateMachine:changeState(self.stateMachine.states.moveState)
    end
end

return DashState