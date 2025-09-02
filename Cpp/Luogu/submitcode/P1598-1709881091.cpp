#include <stdio.h>
#include <string.h>

int main(){
    char tmp;//暂时用来读取字符
    int word[26]={0};//存储每个字母出现的次数
    while(scanf("%c",&tmp)!=EOF){
        switch(tmp){
            case 'A':word[0]++;break;
            case 'B':word[1]++;break;
            case 'C':word[2]++;break;
            case 'D':word[3]++;break;
            case 'E':word[4]++;break;
            case 'F':word[5]++;break;
            case 'G':word[6]++;break;
            case 'H':word[7]++;break;
            case 'I':word[8]++;break;
            case 'J':word[9]++;break;
            case 'K':word[10]++;break;
            case 'L':word[11]++;break;
            case 'M':word[12]++;break;
            case 'N':word[13]++;break;
            case 'O':word[14]++;break;
            case 'P':word[15]++;break;
            case 'Q':word[16]++;break;
            case 'R':word[17]++;break;
            case 'S':word[18]++;break;
            case 'T':word[19]++;break;
            case 'U':word[20]++;break;
            case 'V':word[21]++;break;
            case 'W':word[22]++;break;
            case 'X':word[23]++;break;
            case 'Y':word[24]++;break;
            case 'Z':word[25]++;break;
        }
    }
    for(int i = 0;i<=405;i++){
        int flag = 0,max=0,end=0;//flag标识是否还有星号要输出，0是默认没有了
        for(int j = 0;j<26;j++){//查找当前出现次数最多的字母
            if(word[j]>=max){
                max=word[j];//把出现的次数给max
                end=j;
                if(max!=0){flag=1;}//如果max！=0则说明仍有星号待输出
            }
        }
        if(flag==0){//结束时输出
            printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
            break;//退出循环
        }
        for(int j = 0;j<=end;j++){
            if(word[j]==max){//输出此时和最大次数相同的字母星号
                printf("%s%c",j==0?"":" ",'*');
                word[j]--;
            }
            else{printf("%s%s",j==0?"":" "," ");}
        }
        printf("\n");
    }
    return 0;
}