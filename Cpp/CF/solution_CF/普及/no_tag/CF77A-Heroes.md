# Heroes

## 题目描述

The year of 2012 is coming...

According to an ancient choradrican legend in this very year, in 2012, Diablo and his brothers Mephisto and Baal will escape from hell, and innumerable hordes of demons will enslave the human world. But seven brave heroes have already gathered on the top of a mountain Arreat to protect us mere mortals from the effect of this terrible evil.

The seven great heroes are: amazon Anka, barbarian Chapay, sorceress Cleo, druid Troll, necromancer Dracul, paladin Snowy and a professional hit girl Hexadecimal. Heroes already know how much experience will be given for each of the three megabosses: $ a $ for Mephisto, $ b $ for Diablo and $ c $ for Baal.

Here's the problem: heroes are as much as seven and megabosses are only three! Then our heroes decided to split into three teams, where each team will go to destroy their own megaboss. Each team member will receive a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77A/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) of experience, rounded down, where $ x $ will be the amount of experience for the killed megaboss and $ y $ — the number of people in the team.

Heroes do not want to hurt each other's feelings, so they want to split into teams so that the difference between the hero who received the maximum number of experience and the hero who received the minimum number of experience were minimal. Since there can be several divisions into teams, then you need to find the one in which the total amount of liking in teams were maximum.

It is known that some heroes like others. But if hero $ p $ likes hero $ q $ , this does not mean that the hero $ q $ likes hero $ p $ . No hero likes himself.

The total amount of liking in teams is the amount of ordered pairs $ (p,q) $ , such that heroes $ p $ and $ q $ are in the same group, and hero $ p $ likes hero $ q $ (but it is not important if hero $ q $ likes hero $ p $ ). In case of heroes $ p $ and $ q $ likes each other and they are in the same group, this pair should be counted twice, as $ (p,q) $ and $ (q,p) $ .

A team can consist even of a single hero, but it is important that every megaboss was destroyed. All heroes must be involved in the campaign against evil. None of the heroes can be in more than one team.

It is guaranteed that every hero is able to destroy any megaboss alone.

## 说明/提示

A note to first example: it the first team should be Dracul, Troll and Anka, in the second one Hexadecimal and Snowy, and in the third Cleo и Chapay.

## 样例 #1

### 输入

```
3
Troll likes Dracul
Dracul likes Anka
Snowy likes Hexadecimal
210 200 180
```

### 输出

```
30 3
```

## 样例 #2

### 输入

```
2
Anka likes Chapay
Chapay likes Anka
10000 50 50
```

### 输出

```
1950 2
```

# 题解

## 作者：小杨小小杨 (赞：3)

## 题意
很好懂吧……
## 思路
搜索～    
全排列问题。把 $7$ 人分配到 $3$ 个组，问你如何分配，能使分之差最小，好感度最大。    
好感度定义:当两个人是朋友时，好感度增加。    
注意当 $A$ 喜欢 $B$ 时门票，和 $B$ 喜欢 $A$ 是不同的组。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,t,ma,f[1001][1001],b1[1001],b2[1001],b3[1001],i;
char s1[1001],s[1001],s2[1001];
int mi;
map<string,int> mapp;
void sc(int t,int aa,int bb,int cc,int s){
	if (t==8){
		int h1,h2,h3;
		if (aa==0||bb==0||cc==0) return;
		h1=a/aa;h2=b/bb;h3=c/cc;//个人积分
		if (max(abs(h1-h2),max(abs(h2-h3),abs(h1-h3)))<mi)//最小值
			mi=max(abs(h1-h2),max(abs(h2-h3),abs(h1-h3))),ma=s;
		else if (max(abs(h1-h2),max(abs(h2-h3),abs(h1-h3)))==mi)//最小值下最大值
			ma=max(ma,s);
		return;
	}
	int ss=s;
	for (int i=1;i<=aa;i++){
		if (f[t][b1[i]]) ss++;
		if (f[b1[i]][t]) ss++;//打第一个
	}
	b1[aa+1]=t;sc(t+1,aa+1,bb,cc,ss);b1[aa+1]=0;
	ss=s;
	for (int i=1;i<=bb;i++){
		if (f[t][b2[i]]) ss++;
		if (f[b2[i]][t]) ss++;//打第二个
	}
	b2[bb+1]=t;sc(t+1,aa,bb+1,cc,ss);b2[bb+1]=0;
	ss=s;
	for (int i=1;i<=cc;i++){
		if (f[t][b3[i]]) ss++;
		if (f[b3[i]][t]) ss++;//打第三个
	}
	b3[cc+1]=t;sc(t+1,aa,bb,cc+1,ss);b3[cc+1]=0;
}
int main(){
	scanf("%d",&n);
	mapp["Anka"]=1;
	mapp["Chapay"]=2;
	mapp["Cleo"]=3;
	mapp["Troll"]=4;
	mapp["Dracul"]=5;
	mapp["Snowy"]=6;//把名字转成数字
	mapp["Hexadecimal"]=7;
	for (i=1;i<=n;i++){
		scanf("%s%s%s",s1,s,s2);
		f[mapp[s1]][mapp[s2]]=1;//单向边
	}
	scanf("%d%d%d",&a,&b,&c);
	mi=2e9;
	sc(1,0,0,0,0);//全排列爆搜
	printf("%d %d\n",mi,ma);
	return 0;
}
```


---

