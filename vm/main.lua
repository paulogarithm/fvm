require("vm.glob")
local OpCodes = require("vm.opcodes")


local VmClass = {}

local function GenerateList(filename)
    local file = assert(io.open(filename, "rb"), "File does not exists")
    
    local listOfBytes = {}
    while true do
        local byte = file:read(1)
        if not byte then
            break end
        local byteValue = string.byte(byte)
        table.insert(listOfBytes, byteValue)
    end
    file:close()
    return listOfBytes
end

local function LoadIn(mainTable, insertTable)
    local i = 1
    local j = 1
    local res = 0

    while i <= #mainTable and j <= #insertTable do
        if mainTable[i] == nil then
            mainTable[i] = insertTable[j]
            j = j + 1
        else
            i = i + 1
        end
    end
    res = ((i == (#mainTable + 1)) and i) or i - #insertTable + 1
    while j <= #insertTable do
        table.insert(mainTable, insertTable[j])
        j = j + 1
    end
    return mainTable, res
end

function VmClass.new()
    local res = {
        PC = 0,
        Mem = {},
        Map = {},
        Reg = {},
        Stack = {},

        Load = function (self, filename)
            local instructions = GenerateList(filename)
            local newMem, index = LoadIn(self.Mem, instructions)
            self.Mem = newMem
            self.Map[index] = index + #instructions - 1
            return index
        end,

        Free = function (self, ptrIndex)
            local to = self.Map[ptrIndex]
            assert(to, "Invalid free, nothing here")
            for i = ptrIndex, to do
                self.Mem[i] = nil
            end
            self.Map[ptrIndex] = nil
        end,

        Execute = function (self)
            repeat
                local code = self.Mem[self:IncreasePC()]
                if code == 0x00 then break end
                local F = assert(OpCodes[code], "Instruction doesnt exist")
                F(self)
            until false
        end,

        IncreasePC = function (self, n)
            self.PC = self.PC + (n or 1)
            return self.PC
        end
    }
    return res
end

local function Main()
    assert(#arg >= 1, "Expected at least the binary argument")

    local vm = VmClass.new()
    local a = vm:Load(arg[1])

    vm:Execute()
    print(vm)
    vm:Free(a)
end

local success, err = pcall(Main)
if not success and err then
    io.stderr:write(err .. "\n")
    os.exit(42)
end

