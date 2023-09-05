local op = {}

op[0x05] = function (self)
    local register = self.Mem[self:IncreasePC()]
    local nStr = ""
    for _ = 1, 4 do
        nStr = nStr .. string.format("%02d", self.Mem[self:IncreasePC()])
    end
    local n = assert(tonumber(nStr, 16), "Weird number")
    self.Reg[register] = n
end

op[0x15] = function (self)
    
end

return op