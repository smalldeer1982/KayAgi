# Borya and Hanabi

## 题目描述

Have you ever played Hanabi? If not, then you've got to try it out! This problem deals with a simplified version of the game.

Overall, the game has 25 types of cards (5 distinct colors and 5 distinct values). Borya is holding $ n $ cards. The game is somewhat complicated by the fact that everybody sees Borya's cards except for Borya himself. Borya knows which cards he has but he knows nothing about the order they lie in. Note that Borya can have multiple identical cards (and for each of the 25 types of cards he knows exactly how many cards of this type he has).

The aim of the other players is to achieve the state when Borya knows the color and number value of each of his cards. For that, other players can give him hints. The hints can be of two types: color hints and value hints.

A color hint goes like that: a player names some color and points at all the cards of this color.

Similarly goes the value hint. A player names some value and points at all the cards that contain the value.

Determine what minimum number of hints the other players should make for Borya to be certain about each card's color and value.

## 说明/提示

In the first sample Borya already knows for each card that it is a green three.

In the second sample we can show all fours and all red cards.

In the third sample you need to make hints about any four colors.

## 样例 #1

### 输入

```
2
G3 G3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
G4 R4 R3 B3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
B1 Y1 W1 G1 R1
```

### 输出

```
4
```

# 题解

## 作者：A_zjzj (赞：2)

### 一道细节题

因为英文和数字很少，所以就枚举要提醒的字母和数字，验证是否可以算出来然后再更新答案。

可以推出来的有以下几种：

- 已知颜色，数字未知的只剩下一个

- 已知数字，颜色未知的只剩下一个

- 最后剩下一个

### 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[6][6],k1[6],tot1,k2[6],tot2,ans=25,v[6][6];
char c[3];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",c);
		a[(c[0]=='R'?1:(c[0]=='G'?2:(c[0]=='B'?3:(c[0]=='W'?4:5))))][c[1]-'0']=1;
	}
	for(int i=0;i<(1<<5);i++){
		tot1=0;memset(k1,0,sizeof(k1));
		for(int k=0;k<5;k++)if(i>>k&1)tot1++,k1[k+1]=1;
		for(int j=0;j<(1<<5);j++){
			tot2=0;memset(k2,0,sizeof(k2));
			for(int k=0;k<5;k++)if(j>>k&1)tot2++,k2[k+1]=1;
			if(tot1+tot2>=ans)continue;
			memset(v,0,sizeof(v));
			for(int k=1;k<=5;k++)for(int l=1;l<=5;l++)if(a[k][l]&&k1[k]&&k2[l])v[k][l]=1;
			while(1){
				int t=0;
				for(int k=1;k<=5;k++){
					if(!k1[k])continue;
					int tot=0,p=0;
					for(int l=1;l<=5;l++)if(a[k][l]&&!v[k][l])tot++,p=l;
					if(tot==1)v[k][p]=1,t++;
				}
				for(int k=1;k<=5;k++){
					if(!k2[k])continue;
					int tot=0,p=0;
					for(int l=1;l<=5;l++)if(a[l][k]&&!v[l][k])tot++,p=l;
					if(tot==1)v[p][k]=1,t++;
				}
				if(!t)break;
			}
			int t=0;
			for(int k=1;k<=5;k++)for(int l=1;l<=5;l++)if(a[k][l]&&!v[k][l])t++;
			if(t<=1)ans=tot1+tot2;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xie_lzh (赞：0)

简单结论题。

发现数字和字母种类都很少，可以直接枚举选了那些数字和字母。

一个卡片能被确定有几种情况。

数字字母全被选。

数字被选，同中数字其他字母全被选。

字母被选，同中字母其他数字全被选。

只剩下一个不确定。

简单分讨即可。

[code](https://codeforces.com/contest/442/submission/278750323)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1700}$
---
### 解题思路：

首先发现，相同的卡片在对于结果的贡献上是相同的，所以先对卡片进行一个去重。

然后考虑一张卡片在什么时候能够被确定：

1. 这张卡片的数字和字母都已经能够确定了。
2. 这张卡片的字母或者数字是剩下的卡片中唯一的，且这个数字或者字母能够被确定。
3. 这张卡片是剩下的唯一的一张。

而一个数字或者字母能够被确定当且仅当：

1. 这个数字或者字母被指出来了。
2. 不存在两个或者以上未知的在剩下的未确定牌中的字母或者数字。

枚举指出的数字和字母，然后模拟以上的进程就行了。

---
### 代码：

不建议参考。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,t1[1005],t2[1005],s[1005],tot1[1005],tot2[1005],cnt,ans=2147483647,flag;
int re[1005][1005],c1[1005],c2[1005];
char cc1[1005],cc2[1005];
char get(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' ')c=getchar();
	return c;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cc1[i]=get();cc2[i]=get();
		if(cc1[i]=='R')cc1[i]=0;
		if(cc1[i]=='G')cc1[i]=1;
		if(cc1[i]=='B')cc1[i]=2;
		if(cc1[i]=='Y')cc1[i]=3;
		if(cc1[i]=='W')cc1[i]=4;
		cc2[i]=cc2[i]-'1';
	}
	for(int i=1;i<=n;i++){
		if(re[cc1[i]][cc2[i]]==0){
			cnt++;
			c1[cnt]=cc1[i];
			c2[cnt]=cc2[i];
			re[cc1[i]][cc2[i]]=1;
		}
	}
	n=cnt;
	for(int i=0;i<=(1<<5);i++){
		for(int j=0;j<=(1<<5);j++){
			cnt=0;
			for(int k=0;k<=4;k++){
				if((i>>k)&1)t1[k]=1,cnt++;
				else t1[k]=0;
			}
			for(int k=0;k<=4;k++){
				if((j>>k)&1)t2[k]=1,cnt++;
				else t2[k]=0;
			}
			if(ans<cnt)continue;
			
			for(int k=1;k<=n;k++)s[k]=0;
			
			for(int k=1;k<=n;k++)
			if(t1[c1[k]]==1&&t2[c2[k]]==1)s[k]=1;
			
			for(int k=0;k<=4;k++)tot1[k]=tot2[k]=0;
			
			for(int k=1;k<=n;k++)
			if(s[k]==0){
				tot1[c1[k]]++;
				tot2[c2[k]]++;
			}
			
			flag=1;
			while(flag){
				flag=0;
				
				int flag1=6;
				for(int k=0;k<=4;k++)
				if(tot1[k]==1&&t1[k]==1)flag1=k;
				for(int k=1;k<=n;k++){
					if(s[k])continue;
					if(c1[k]==flag1){
						tot1[c1[k]]--;
						tot2[c2[k]]--;
						s[k]=1;
						flag=1;
					}
				}
				
				flag1=6;
				for(int k=0;k<=4;k++){
					if(t1[k])continue;
					if(tot1[k]==1){
						if(flag1==6)flag1=k;
						else flag1=7;
					}
					if(tot1[k]>1)flag1=7;
				}
				for(int k=1;k<=n;k++){
					if(s[k])continue;
					if(c1[k]==flag1){
						tot1[c1[k]]--;
						tot2[c2[k]]--;
						s[k]=1;
						flag=1;
					}
				}
				
				flag1=6;
				for(int k=0;k<=4;k++){
					if(tot2[k]==1&&t2[k]==1)flag1=k;
				}
				for(int k=1;k<=n;k++){
					if(s[k])continue;
					if(c2[k]==flag1){
						tot1[c1[k]]--;
						tot2[c2[k]]--;
						s[k]=1;
						flag=1;
					}
				}
				
				flag1=6;
				for(int k=0;k<=4;k++){
					if(t2[k])continue;
					if(tot2[k]==1){
						if(flag1==6)flag1=k;
						else flag1=7;
					}
					if(tot2[k]>1)flag1=7;
				}
				for(int k=1;k<=n;k++){
					if(s[k])continue;
					if(c2[k]==flag1){
						tot1[c1[k]]--;
						tot2[c2[k]]--;
						s[k]=1;
						flag=1;
					}
				}
			}
			
			flag=0;
			for(int k=1;k<=n;k++)if(s[k]==0)flag++;
			if(flag<=1)ans=min(ans,cnt);
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*


25
B3 Y1 R3 Y3 R5 B4 B3 G1 R1 B4 B5 W3 R4 W1 B3 Y3 B3 Y4 B2 G5 Y1 G5 R4 B5 Y1



25
W1 W3 
G1 G5 
B2 B3 B4 B5 
R1 R3 R4 R5 
Y1 Y3 Y4 


RGBYW

25
W1 W3 
G1 G5 
B2 B5 
R5  

G B R Y
1 3 4 
*/
```


---

