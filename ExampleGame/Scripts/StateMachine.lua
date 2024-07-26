local StateMachine = {}

function StateMachine:new(initiallState)
    local obj = {}
    setmetatable(obj, self)
    self.__index = self
    obj.curState = initiallState
    return obj
end

function StateMachine:changeState(newState)
    local curState = self.curState
    if curState and curState.exit then
        curState:exit()
    end
    curState = newState
    if curState.enter then
        curState:enter()
    end
    self.curState = curState
end

function StateMachine:update()
    local curState = self.curState
    if curState and curState.update then
        curState:update()
    end
end

return StateMachine