local PlayerScript = scriptTemplate.new()

PlayerScript.create = function(entity)
    print("Create Player")
end
    
PlayerScript.update = function(entity, dt)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local speed = luaComponent.table.MaxSpeed
    local moveInput = GameData.input:getInputAxis2("Move")
    transformComponent.translation.x = transformComponent.translation.x + moveInput.x * speed
    transformComponent.translation.y = transformComponent.translation.y - moveInput.y * speed
end

PlayerScript.destroy = function(entity)

end

return PlayerScript