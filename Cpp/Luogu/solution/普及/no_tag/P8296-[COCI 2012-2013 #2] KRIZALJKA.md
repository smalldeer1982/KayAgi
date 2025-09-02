# [COCI 2012/2013 #2] KRIZALJKA

## 题目背景

**本题分值按 COCI 原题设置，满分 $80$。**

## 题目描述

你喜欢玩填字游戏吗？如果是，你可能会知道传统的初学游戏，如下所示：

***

![](https://cdn.luogu.com.cn/upload/image_hosting/pi8lxkai.png)

- 水平方向上：

  1. 用于冷却电脑的设备

  2. 固态水

  3. 用来获得

- 垂直方向上：

  1. 又小又软又甜的水果
  
  2. 强力纸牌
  
  3. 渔夫的工具
***

给定六个有三个字母的单词，你需要把它们放在 $3\times 3$ 的方格上，使得水平与垂直均出现这几个单词。


## 样例 #1

### 输入

```
ANA
ANA
DAR
DAR
RAD
RAD```

### 输出

```
DAR
ANA
RAD```

## 样例 #2

### 输入

```
EVO
HEP
HIR
IVA
PAD
ROD```

### 输出

```
HEP
IVA
ROD```

## 样例 #3

### 输入

```
AKO
CES
DOC
DON
ESI
KES```

### 输出

```
0```

# 题解

## 作者：褚橙 (赞：3)

这里是蒟蒻第一次写题解，有错误请多多指教。

### 思路
第一眼一看就是黄题搜索，再一看，其实是一道普通的模拟。

采用4重循环的方法：
1. 前三重循环枚举三给不同的字符串。
2. 将字符串组合。
3. 最后一个循环判断字符串是否成立。

注：因为输入是按字典序，所以不用再排序。

### 样例模拟
```c
1. ANA
2. ANA
3. DAR
4. DAR
5. RAD
6. RAD
```
可以写成：

```
  3 1 5
4 D A R
2 A N A
6 R A D
```

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n=6;//这里n均为6
string a[10];
int main()
{
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)//枚举三个数
			{
				if(i==j||j==k||k==i)//判重
				{
					continue;
				}
				string x;
				x=x+a[i][0]+a[j][0]+a[k][0];
				string y;
				y=y+a[i][1]+a[j][1]+a[k][1];
				string z;
				z=z+a[i][2]+a[j][2]+a[k][2];
				//分别令 x,y,z 为第一列，第二列，第三列
				bool f1=0,f2=0,f3=0;
				//成功的就可以标记
				for(int l=1;l<=n;l++)
				{
					if(l==i||l==j||l==k)
					{
						continue;
					}
					if(a[l]==x&&!f1)//会有重复的记得判重
					{
						f1=1;
					}
					else if(a[l]==y&&!f2)//同上
					{
						f2=1;
					}
					else if(a[l]==z)
					{
						f3=1;
					}
				}
				if(f1&&f2&&f3)//成功了直接输出，并结束
				{
					cout<<a[i]<<endl;
					cout<<a[j]<<endl;
					cout<<a[k]<<endl;
					return 0;
				}
			}
		}
	}
	cout<<0<<endl;//未成功的输出0
	return 0;
}
```
这样就可以AC啦。

---

## 作者：紊莫 (赞：2)

> upd 2022.7.8：修改了对 $map$ 做法的解释以及删去了一个错误的小方法。

简单看了下题解区，两位搜索的和一位循环枚举的。我个人倾向于循环的方式。  
# 题意

在六个字符串中选三个组成矩阵，矩阵中的横竖六个字符串刚好是这六个原串的字典序最小的方案。

# 分析

>输入保证按字典序给出。

这句话说明了我们在枚举答案时不需要统一储存取最小的，只要输出第一个答案即可。  

接下来谈一些细节方面的实现方式。  

当枚举出三个字符串时比较容易得到纵向的三个字符串。  
然而目前的题解似乎想复杂了，其实不需要一一判断其唯一性。  

方法是把所有的六个字符串（包括枚举的和求出的）排序后连接起来，然后将原来的序列也这样操作，比较两者是否一致就可以了。  

# 代码

基于以上思路，代码见下。  

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[10],T,check;
bool flag=1;
int main()
{
	for(int i=1;i<=6;i++) cin>>s[i],check=check+s[i];
	for(int i=1;i<=6;i++)for(int j=1;j<=6;j++)for(int k=1;k<=6;k++)
		if(i!=j&&j!=k&&i!=k)
		{
			string px[10];
			for(int l=0;l<=2;l++)
				px[l+1]=T+s[i][l]+s[j][l]+s[k][l];
			px[4]=s[i],px[5]=s[j],px[6]=s[k];
			sort(px+1,px+7);
			string fl="";
			for(int l=1;l<=6;l++) fl=fl+px[l];
			if(fl==check)
			{
				cout<<s[i]<<endl<<s[j]<<endl<<s[k]<<endl;flag=0;
				return 0;
			}
		}
	if(flag) cout<<0;
}
```

**注意到一段代码。**

```cpp
for(int l=0;l<=2;l++)
	px[l+1]=T+s[i][l]+s[j][l]+s[k][l];
```

这段代码中的 ```T``` 是什么？  
其实在这一点上我借鉴了 @xt__ 的代码。如果去掉这个或者改成空字符串都会有 bug。例如去掉就会变成空值，加上空字符串会是乱码。  

之前我说这题不能用 map 来解决，但其实遇到样例 1 这样的相同情况我们比较的就不是其**存在性**，而是直接比较其出现的次数和原来的是否一致即可。  

同时弥补之前的学术谬误，此处再给出代码。  

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[10],T;
map<string,int> ans;
int main()
{
    for(int i=1;i<=6;i++) cin>>s[i],ans[s[i]]++;
    for(int i=1;i<=6;i++)for(int j=1;j<=6;j++)for(int k=1;k<=6;k++)
        if(i!=j&&j!=k&&i!=k)
        {
			map<string,int> mp;
			int flag2=1;
			string px[10];
            for(int l=0;l<=2;l++) px[l+1]=T+s[i][l]+s[j][l]+s[k][l]; 
			px[4]=s[i],px[5]=s[j],px[6]=s[k];
            for(int i=1;i<=6;i++) mp[px[i]]++;
			for(int i=1;i<=6;i++) if(!mp[s[i]]||mp[s[i]]!=ans[s[i]]) flag2=0;
            if(flag2)
            {
                cout<<s[i]<<endl<<s[j]<<endl<<s[k]<<endl;
                return 0;
            }
        }
    cout<<0;
}
```


---

## 作者：_Spectator_ (赞：2)

[可能更好的食用体验](/blog/523641/P8296) $|$ 
[题目传送门](/problem/P8296) $|$ 
[我的其他题解](/blog/523641/#type=题解)

------------

${\large\color{#00CD00}\text{主要思路}}$

很多大佬这题都是用搜索来做的。但其实这道题只需要用三重循环枚举就可以了。

大体思路如下：

1. 枚举 $3$ 个单词。
2. 将它们竖着排列，生成 $3$ 个新的单词。
3. 判断生成的 $3$ 个单词是否对应剩余的 $3$ 个单词。
4. 如果是，与已有的答案进行比较，输出字典序最小的方案。

需要注意的是，即使有多个单词相同，它们仍应当成不同的单词进行判断。也就是说，如果 $2$ 个单词相同，那么在答案中也应该体现 $2$ 个这个单词。

例如第一个样例的答案：
```txt
DAR
ANA
RAD
```
这里横着和竖着分别有 $2$ 个`DAR`、$2$ 个`ANA`、$2$ 个`RAD`，它们分别了对应输入样例中的 $2$ 个`DAR`、$2$ 个`ANA`和 $2$ 个`RAD`。

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>　
#define for(i,a,b) for(int i=a;i<=b;i++)　
using namespace std;　
string tmp,s[10],t[5],ans="hello";　
int main()　
{　
	for(i,1,6)cin>>s[i];　
    for(a,1,6)for(b,1,6)for(c,1,6)//枚举3个单词 
    {　
    	if(a==b||a==c||b==c)continue;//如果重复了则跳过 
	   	for(i,0,2)t[i+1]=tmp+s[a][i]+s[b][i]+s[c][i];//竖着生成3个单词。直接用 ""+char 不行，要用一个空string来加 
		for(i,1,6)//找剩余3个单词 
		{　
			if(i==a||i==b||i==c)continue;　
			for(j,1,3)　
				if(t[j]==s[i]){t[j]="";goto brk;}//如果对应要将这个单词清空，否则后面相同的单词也会与这个单词对应 
			goto brak;brk:;　
		}　
		tmp=s[a]+'\n'+s[b]+'\n'+s[c];//中间加个换行符，后面输出可以直接换行 
		if(tmp<ans)ans=tmp;　
		brak:tmp="";　
	}　
	if(ans=="hello")cout<<0;　
	else cout<<ans;　
    return 0;　
}　
```

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：ZepX_D (赞：2)

## 题意
给出 $ 6 $ 个单词，让你输出一个 $ 3 \times 3 $ 的矩阵，使它水平 $ 3 $ 行和竖直 $ 3 $ 列包含这 $ 6 $ 个单词

## 分析
因为只有 $ 6 $ 个单词，所以完全可以搜索，因为单词是按字典序大小给出的，所以就不用再排序了，思路就是暴力枚举这个矩阵的$ 3 $ 行，这 $ 3 $ 行填完了就看竖直 $ 3 $ 列符不符合就可以了

## 代码
```cpp
#include<cstdio>
#include<string>
#include<iostream>

using namespace std;

bool f;
string s[7];
char ch[4][4];//记录矩阵
bool vis[7];//记录单词选择情况，避免重复选择
void dfs(int a,int pos)//pos为第几个单词
{
	if(f) return;//有答案就不必再搜了
	if (a<=3)
	{
    	//记录第a行
		ch[a][1]=s[pos][0];
		ch[a][2]=s[pos][1];
		ch[a][3]=s[pos][2];
		for (int i=1;i<=6;i++)
		{
			if (vis[i]) continue;//选了就跳过
			vis[i]=1;
			dfs(a+1,i);
			vis[i]=0;//回溯
		}
	}
	else
	{
		//比对第a-3列，不符合直接return
		if (ch[1][a-3]!=s[pos][0])
			return;
		if (ch[2][a-3]!=s[pos][1])
			return;
		if (ch[3][a-3]!=s[pos][2])
			return;
		if (a==6)//已经找到符合题意的矩阵
		{
			//当前情况即为字典序最小情况，因为我们是从前往后选的
			for (int i=1;i<=3;i++)
				printf("%c%c%c\n",ch[i][1],ch[i][2],ch[i][3]);
			f=1;//已经有答案了
			return;
		}
		for (int i=1;i<=6;i++)
		{
			if (vis[i]) continue;
			vis[i]=1;
			dfs(a+1,i);
			vis[i]=0;
		}

	}
	return ;
}

int main()
{
	for (int i=1;i<=6;i++)
		cin>>s[i];
	for (int i=1;i<=6;i++)
	{
		vis[i]=1;
		dfs(1,i);
		vis[i]=0;
	}
	if (!f) printf("0");
	return 0;
}
```

---

## 作者：Marshall001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8296)

## 题目大意

给定六个有三个字母的单词，把它们放在一个 $3\times 3$ 的矩阵里，使得水平与垂直均出现这几个单词。

## 思路

首先枚举 $3$ 个字母，代表水平的 $3$ 个单词，然后枚举剩下的 $3$ 个单词，如果剩下的 $3$ 个单词均为垂直的 $3$ 个单词，那么就输出，否则输出 $0$。

例如样例 $1$。$3,1,5$ 为水平的单词，$4,2,6$ 均为垂直的单词。

**因为输入保证按字典序给出，所以不用排序。**

## 代码

```cpp
#include <iostream>
using namespace std;
string s[10];
int main(){
	for(int i=1;i<=6;i++){
		cin>>s[i];//输入字符串
	}
	for(int x=1;x<=6;x++){//枚举第一个
		for(int y=1;y<=6;y++){//枚举第二个
			for(int z=1;z<=6;z++){//枚举第三个
				if(x==y||x==z||y==z){
					continue;//去重
				}
				string a,b,c;//垂直的三个
				a=a+s[x][0]+s[y][0]+s[z][0];
				b=b+s[x][1]+s[y][1]+s[z][1];
				c=c+s[x][2]+s[y][2]+s[z][2];
				for(int i=1;i<=6;i++){
					if(i==x||i==y||i==z){
						continue;//去重
					}
					if(s[i]==a){
						a="";//如果找到了，那么将a赋值成一个“”串，去重
					}
					else if(s[i]==b){
						b="";//同上
					}
					else if(s[i]==c){
						c="";//同上
					}
				}
				if(a==b&&b==c&&a==""){//如果都找到了
					cout<<s[x]<<endl<<s[y]<<endl<<s[z];//那么输出
					return 0;
				}
			}
		}
	}
	cout<<"0";//如果找到现在还没有找到，那么输出0
	return 0;
}
```

## THE END

---

## 作者：newbeeglass (赞：0)

题目中：
```
使得水平与垂直均出现这几个单词
```
意思为六个单词在这个方格中都出现过。

因为数据小，很快就能想到枚举，既然要保证单词全部出现，那就先枚举 $3$ 个单词放入 $3$ 行或 $3$ 列中，再判断其它 $3$ 个单词是否在 $3$ 行或 $3$ 列中全出现（如果枚举行，就判断列，反之亦然）。题目保证输入单词按字典序排好，那么只要按题目顺序枚举，所得的第一个合法方案就是字典序最小的方案。

具体讲一下代码实现：首先开两个二维数组 ```a``` 和 ```s```，```a``` 为输入数据，```s``` 为生成的方案。枚举很简单，记住别枚举重复就好了，我选择枚举行。对于判断 ```s``` 是否合法，需要另开一个 ```bool``` 型数组 ```b```，标记单词是否出现过，初始值全为 $0$，枚举的 $3$ 个单词直接标记为 $1$，然后判断三个列是否包含剩下的 $3$ 个单词，可以开三重 ```for``` 循环，第一层是枚举 ```s``` 的列，第二层枚举单词，如果这个单词没被标记过，进入第三层，看这一列是否为这个单词，如果是，那么把这个单词标为 $1$，最后看是不是所有单词都被标为 $1$ 就好了，具体看代码。

### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[7][4],s[4][4];
bool check(int x,int y,int z){
	bool b[7]={};
	b[x]=1;
	b[y]=1;
	b[z]=1;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=6;j++){
			if(b[j]){
				continue;
			}
			bool flag2=0; 
			for(int k=1;k<=3;k++){ 
				if(s[k][i]!=a[j][k]){
					flag2=1;
					break;
				}
			}
			if(!flag2){
				b[j]=1;
				break;
			}
		}
	}
	if(b[1] && b[2] && b[3] && b[4] && b[5] && b[6]){
		return 1;
	}
	return 0;
}
int main(){
	for(int i=1;i<=6;i++){
		for(int j=1;j<=3;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=6;i++){
		for(int j=1;j<=6;j++){
			for(int k=1;k<=6;k++){
				if(i!=j && j!=k && i!=k){
					for(int l=1;l<=3;l++){
						s[1][l]=a[i][l];
						s[2][l]=a[j][l];
						s[3][l]=a[k][l];
					}
					if(check(i,j,k)){
						for(int m=1;m<=3;m++){
							cout<<s[m][1]<<s[m][2]<<s[m][3]<<endl;
						}
						return 0;
					}
				}
			}
		}
	}
	cout<<0;
}

```


---

