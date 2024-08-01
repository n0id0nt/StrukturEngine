print("Test 1")

local gameObjects = 
{
    player = "Test",
}

--Script.create = function(dt)
--    -- add components to each 
--    print("Test 2")
--end

Script.update = function(dt)
    print("Test 2")
    local entity = GameData:getEntitiesWithIdentifier("Player")[1] -- should only be one
    local playerTransform = GameData:getTransformComponent(entity)
    playerTransform.translation.x = playerTransform.translation.x + 0.5
    playerTransform.translation.y = playerTransform.translation.y + 0.5
end
