local HelperFunctions = {}

--------------------------------------------------------------
--HELPER FUNCTIONS
--------------------------------------------------------------
function HelperFunctions.MoveTowards(currentValue, targetValue, speed)
    local direction = targetValue - currentValue
    local magnitude = math.abs(direction)

    if magnitude > speed then
        local normalizedDirection = direction / magnitude
        local newValue = currentValue + normalizedDirection * speed
        return newValue
    else
        return targetValue
    end
end

function HelperFunctions.Clamp(value, minValue, maxValue)
    return math.max(minValue, math.min(value, maxValue))
end

function HelperFunctions.copyTable(originalTable)
    local copy = {}
    for key, value in pairs(originalTable) do
        if type(value) == "table" then
            copy[key] = copyTable(value) -- recursively copy subtables
        else
            copy[key] = value
        end
    end
    return copy
end

return HelperFunctions