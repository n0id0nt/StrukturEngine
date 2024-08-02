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
    local move = GameData.input:getInputAxis2("Move")
    playerTransform.translation.x = playerTransform.translation.x + move.x
    playerTransform.translation.y = playerTransform.translation.y - move.y
end
