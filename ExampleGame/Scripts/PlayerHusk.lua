local PlayerHuskScript = {} --scriptTemplate.new()

PlayerHuskScript.create = function(entity, dt, systemTime)
    local spriteComponent = GameData:createSpriteComponent(entity)
    spriteComponent:setImage("../ExampleGame/Tiles/PlayerGrowthSprites.png", 5, 12, 54, GameData.resourcePool)
    spriteComponent.offset = vec2.new(32,32)
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    entityTable.collisionRec = rectangle.new(-32,-32,64,64)
end

PlayerHuskScript.update = function(entity, dt, systemTime)

end

PlayerHuskScript.destroy = function(entity)

end

return PlayerHuskScript