
local Player_Script = require("Player")

local gameObjects = 
{
    Player = Player_Script,
} 

Script.initialise = function(dt)
    -- initialise each component
    for objectIdentifier, script in pairs(gameObjects) do
        local entities = GameData:getEntitiesWithIdentifier(objectIdentifier)
        for _, entity in ipairs(entities) do
            script.create(entity)
            local luaComponent = GameData:getLuaComponent(entity)
            luaComponent.initalised = true
        end
    end
end

Script.update = function(dt)
    for objectIdentifier, script in pairs(gameObjects) do
        local entities = GameData:getEntitiesWithIdentifier(objectIdentifier)
        for _, entity in ipairs(entities) do
            local luaComponent = GameData:getLuaComponent(entity)
            if not luaComponent.initalised then
                script.create(entity)
                luaComponent.initalised = true
            end
            
            script.update(entity, dt)
        end
    end
end
