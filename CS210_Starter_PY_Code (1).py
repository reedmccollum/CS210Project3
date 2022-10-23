import re
import string



def printsomething():
    print("Hello from python!")


def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v


#   BasicRead  
#       Param:  none
#       Return: List
#   BasicRead is a file reading function that intakes a file of names of items and makes a list of 
#   them uniquely with their frequency in individual lists.

def BasicRead():
    listOfItemAndFreq = []
    f = open("ItemList.txt", "r")
    wholeFile = f.read()
    fileSplit = wholeFile.split('\n')
    isPresent = True
    count = 0
    for line in fileSplit:
        count+=1
        isPresent = True
        if count == 1:
            firstList = [line, fileSplit.count(line)]
            listOfItemAndFreq.append(firstList)
        else:
            
            for list in listOfItemAndFreq:
                if line == list[0]:
                    isPresent = True
                    break
                elif line != list[0]:
                    isPresent = False
                
        if isPresent == False:
            listOfItemAndFreq.append([line, fileSplit.count(line)])
        
   
    f.close()
    return listOfItemAndFreq
 
 
#   ListItems
#       Param:  none
#       Return: none
#   Uses list made by BasicRead and prints each item with its frequency

def ListItems():
    listOfItems = BasicRead()
    for item in listOfItems:
        print("{} {}".format(item[0], item[1]))
    

#   ChooseItem
#       Param: string
#       Return: int
#   ChooseItem intakes the string of the item they are looking for, and checks the list. If found, it will return
#   the frequency. If not found, it will return 0.

def ChooseItem(selectedItem):
    listOfItems = BasicRead()
    for items in listOfItems:
        if items[0] == selectedItem:
            return items[1]

    return 0


#   WriteToFile
#       Param:  none
#       Return: none
#   Uses list from BasicRead and either rights to file frequency.dat or creates and writes to it.


def WriteToFile():
    listOfItems = BasicRead()
    f = open("frequency.dat", "w")
    for item in listOfItems:
        f.write("{} {}\n".format(item[0], item[1]))
    f.close()
    

#   MakeHistogram
#       Param:  none
#       Return: none
#   Call WriteToFile and uses frequency.dat to figure out frequency per item and print out the respective number
#   of stars


def MakeHistogram():
    WriteToFile()
    f = open("frequency.dat", "r")
    wholeFile = f.read()
    fileSplit = wholeFile.split("\n")
    
    for entry in fileSplit:
        splitData = entry.split(' ')
        
        histogramStars = ""
        freqInt = int(splitData[1])
        count = 0
        while count < freqInt:
            histogramStars += "*"
            count +=1
        print("{} {}".format(splitData[0], histogramStars))
