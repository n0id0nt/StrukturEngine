local PlayerScript = scriptTemplate.new()

PlayerScript.create = function(entity)
    print("Create Player")
    local cameraComponent = GameData:createCameraComponent(entity)
    cameraComponent.cameraPriority = 1
    cameraComponent.zoom = 3
    cameraComponent.damping = vec2.new(3,3)
    cameraComponent.forcePosition = true
    local spriteComponent = GameData:createSpriteComponent(entity)
    spriteComponent:setImage("../ExampleGame/Tiles/Warrior_Sheet-Effect.png", 17, 6, 0, GameData.resourcePool)
end
    
PlayerScript.update = function(entity, dt)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local cameraComponent = GameData:getCameraComponent(entity)
    local speed = luaComponent.table.MaxSpeed
    local moveInput = GameData.input:getInputAxis2("Move")
    transformComponent.translation.x = transformComponent.translation.x + moveInput.x * speed * dt
    transformComponent.translation.y = transformComponent.translation.y - moveInput.y * speed * dt
    if GameData.input:isInputDown("Jump") then
        cameraComponent:addTrauma(0.15)
    end
end

PlayerScript.destroy = function(entity)

end

return PlayerScript