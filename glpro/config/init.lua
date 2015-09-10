local meta_table = {}
meta_table.__index = function(t, k)
    if rawget(t, k) == nil then
        return function(...)
            return { k, ... }
        end
    end

    return rawget(t, k)
end

setmetatable(_G, meta_table)

function d_print(t)
    local has_printed = {}
    local function inner_print(t, head)
        for k, v in pairs(t) do
            print(head .. "" .. tostring(k) .. ": " .. tostring(v))
            if type(v) == "table" and not has_printed[v] then
                inner_print(v, head .. "   ")
            end
            has_printed[v] = true
        end
    end
    inner_print(t, "")
end


