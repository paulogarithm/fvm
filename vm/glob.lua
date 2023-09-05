local originPrint = print

local function DisplayTable(a, layer, name)
    local str = "\x1b[35;1mList:\x1b[m\n"

    for k, v in pairs(a) do
        if type(v) == "function" then goto continue end
        str = str .. string.rep("\t", layer) .. "[" .. ((type(k) == "number" and name and name:sub(1, 3) == "Mem")
                and string.format("0x%04x", k)
                or ((type(k) == "number" and name and string.sub(name, 1, 3) == "Map")
                    and string.format("0x%04x", k)
                    or tostring(k))) .. "]\t" ..

            (type(v) == "table"
                and DisplayTable(v, layer + 1, k)
                or ((type(v) == "number" and name and string.sub(name, 1, 3) == "Mem")
                    and string.format("%02x", v)
                    or ((type(v) == "number" and name and string.sub(name, 1, 3) == "Map")
                        and string.format("0x%04x", v)
                        or tostring(v)))) .. "\n"

        ::continue::
    end
    return str
end

_G.print = function(...)
    local args = { ... }
    for key, arg in ipairs(args) do
        if type(arg) == "table" then
            originPrint(DisplayTable(arg, 0, key))
        else
            originPrint(arg)
        end
    end
end
