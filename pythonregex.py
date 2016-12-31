#Chase Kyle
#simple text document validater using python regex
#format: record number | size | username | transaction | field type | numeric_value | character_value | date_value'
#only one of the three fields can be populated in each entry

import re
text_file = open("pl1.txt", "r")
out_file = open("pl2.txt", "w")
count = 1
nCount = 0
dCount = 0
cCount = 0
#validate function if field type for the line is numeric
def validateIfN(line):
    reg1=r"[|]N[|][-+]?\d+\.?\d*[|] [|] [|]$"
    if re.findall(reg1, line):
        outLine = "Line %s OK --- %s" %(count, line)
        out_file.writelines(outLine)
    else:
        global nCount
        nCount = nCount + 1
        outLine = "Line %s NO --- %s (was expecting only numerical value that is atleast an integer)\n" %(count, line)
        out_file.write(outLine)
#validate function if field type for the line is character
def validateIfC(line):
    reg2=r"[|]C[|] [|][a-z][|] [|]$"
    if re.findall(reg2, line):
        outLine = "Line %s OK --- %s" %(count, line)
        out_file.write(outLine)
    else:
        global cCount
        cCount = cCount + 1
        outLine = "Line %s NO --- %s (was expecting only a single character)\n" %(count, line)
        out_file.write(outLine)
#validate function if field type for the line is date
def validateIfD(line):
    reg3=r"[|]D[|] [|] [|](1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}[|]$"
    if re.findall(reg3,line):
        outLine = "Line %s OK --- %s" %(count,line)
        out_file.write(outLine)
    else:
        global dCount
        dCount = dCount + 1
        outLine = "Line %s NO --- %s (was expecting a valid date)\n" %(count,line)
        out_file.write(outLine)
regex1 = "[|]C[|]"
regex2 = "[|]D[|]"
regex3 = "[|]N[|]"
#validate each line in file
for line in text_file:
    if re.findall(regex1, line):
        validateIfC(line)
    elif re.findall(regex2, line):
        validateIfD(line)
    else:
        validateIfN(line)
    count += 1
text_file.close()
out_file.close()
done_file = open("pl2.txt", "r")
print(done_file.read())
print("There were %s Numerical_Value Errors, %s Character_Value Errors, and %s Date_Value errors") %(nCount, cCount, dCount)
done_file.close()
