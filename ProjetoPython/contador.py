import re
from collections import Counter
from sys import argv
def main():
    sup=int(argv[2])
    inf=int(argv[3])
    
    words=re.findall(r'\w+', open(str(argv[1]),"r").read().lower())
    with open("saida_"+ str(argv[1]),'w+') as outFile:
        ordem=Counter(words).most_common()
	for i in ordem:
            if i[1] > inf and i[1]<sup:
                outFile.write(str(i[0]) + "\t" + str(i[1]) + "\n",)
            
if __name__=='__main__':
    main()
