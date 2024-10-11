local WizzardScript = {}-- scriptTemplate.new()

WizzardScript.create = function(entity, dt, systemTime)
    local spriteComponent = GameData:createSpriteComponent(entity)
    spriteComponent:setImage("../ExampleGame/Tiles/PlayerGrowthSprites.png", 5, 12, 55, GameData.resourcePool)
    spriteComponent.offset = vec2.new(32,32)
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    entityTable.collisionRec = rectangle.new(-32,-32,64,64)

    local cameraComponent = GameData:createCameraComponent(entity)
    cameraComponent.cameraPriority = 0
    cameraComponent.zoom = 4
    cameraComponent.damping = vec2.new(3,3)

    local spriteAnimationComponent = GameData:createSpriteAnimationComponent(entity)
    local idleAnimation = spriteAnimation.new(55, 59, 1, true)
    spriteAnimationComponent:addAnimation("idle", idleAnimation)
    spriteAnimationComponent:playAnimation("idle", systemTime)

end

WizzardScript.update = function(entity, dt, systemTime)

end

WizzardScript.destroy = function(entity)

end

return WizzardScript