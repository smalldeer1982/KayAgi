# Planet Lapituletti

## 题目描述

The time on the planet Lapituletti goes the same way it goes on Earth but a day lasts $ h $ hours and each hour lasts $ m $ minutes. The inhabitants of that planet use digital clocks similar to earth ones. Clocks display time in a format HH:MM (the number of hours in decimal is displayed first, then (after the colon) follows the number of minutes in decimal; the number of minutes and hours is written with leading zeros if needed to form a two-digit number). Hours are numbered from $ 0 $ to $ h-1 $ and minutes are numbered from $ 0 $ to $ m-1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/60f2fad68c8c57b27eed490aaadafcab0fd86b23.png)That's how the digits are displayed on the clock. Please note that digit $ 1 $ is placed in the middle of its position.

A standard mirror is in use on the planet Lapituletti. Inhabitants often look at the reflection of the digital clocks in the mirror and feel happy when what you see on the reflected clocks is a valid time (that means that you see valid digits in the reflection and this time can be seen on the normal clocks at some moment of a day).

The image of the clocks in the mirror is reflected against a vertical axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/45e02f44df121c5701b96d2a2728d34df90fea6a.png)The reflection is not a valid time.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/a42f523b339fb6fa2f4820a2d60d05f67a7624be.png)

The reflection is a valid time with $ h=24 $ , $ m = 60 $ . However, for example, if $ h=10 $ , $ m=60 $ , then the reflection is not a valid time.

An inhabitant of the planet Lapituletti begins to look at a mirrored image of the clocks at some time moment $ s $ and wants to know the nearest future time moment (which can possibly happen on the next day), when the reflected clock time is valid.

It can be shown that with any $ h $ , $ m $ , $ s $ such a moment exists. If the reflected time is correct at the moment the inhabitant began to look at the clock, that moment is considered the nearest.

You are asked to solve the problem for several test cases.

## 说明/提示

In the second test case it is not hard to show that the reflection of 23:59 is incorrect, while the reflection of the moment 00:00 on the next day is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/50d79fafef9eb95bbfe6fa29f77ca1c6567a1615.png)

## 样例 #1

### 输入

```
5
24 60
12:21
24 60
23:59
90 80
52:26
1 100
00:01
10 10
04:04```

### 输出

```
12:21
00:00
52:28
00:00
00:00```

# 题解

## 作者：LinkZelda (赞：3)

- **题意简述：**

给定一个形如 `HH:MM` 的时间，与 $h$ 和 $m$ 的范围，找出一个最近的时间（只能是**现在或者未来**的时间），使得这个时间与它镜像翻转后的时间均合法。

- $Solution$:

发现 $n,m\leq 100$，于是我们可以考虑直接枚举经过了的时间，然后判断该时间是否合法即可。

注意一些实现上的小细节，比如前导 $0$ 之类的。

具体可以看一下我的赛时代码。

- **代码如下：**

```cpp
#include<cstdio>
#include<algorithm>
#include<ctype.h>
#include<iostream>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
 }

int to[10]={0,1,5,1000,1000,2,1000,1000,8,1000};//镜面翻转后的数，如果翻转过来不是一个数，就设为极大值保证它不合法。

int t,h,m;
string s;


bool check(int nowh,int nowm,int k)
{
	int hh=k/m;
	int nh=nowh+hh;
	k-=hh*m;
	int mm=k;
	int nm=nowm+mm;
	if(nm>m-1)
	{
		nh++;
		nm-=m;
	}	
	if(nh>h-1)
	{
		printf("00:00\n");
		return true;
	}
	int ansh=0,ansm=0;
	int reth=nh,retm=nm;
	if(nm<10)
		ansh=to[nm%10]*10;
	else while(nm)
	{
		ansh=ansh*10+to[nm%10];
		nm/=10;
	}
	if(nh<10)
		ansm=to[nh%10]*10;
	else while(nh)
	{
		ansm=ansm*10+to[nh%10];
		nh/=10;
	}
	if(0<=ansm&&ansm<=m-1&&0<=ansh&&ansh<=h-1)
	{
		if(reth<10)
		{
			printf("0%d:",reth);
		}
		else
			printf("%d:",reth);
		if(retm<10)
		{
			printf("0%d\n",retm);
		}
		else
			printf("%d\n",retm);
		return true;
	}
	return false;
}

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>h>>m;
		cin>>s;
		int nowh=0,nowm=0;
		for(int i=0;i<=1;i++)
			nowh=nowh*10+s[i]-'0';
		for(int i=3;i<=4;i++)
			nowm=nowm*10+s[i]-'0';
		if(0<=nowh&&nowh<=h-1&&0<=nowm&&nowm<=m-1)
		{
			
			int ansh=0,ansm=0;
			int nh=nowh,nm=nowm;
			if(nm<10)
				ansh=to[nm%10]*10;
			else while(nm)
			{
				ansh=ansh*10+to[nm%10];
				nm/=10;
			}
			//printf("!?%d\n",nh);
			if(nh<10)
				ansm=to[nh%10]*10;
			else while(nh)
			{
				ansm=ansm*10+to[nh%10];
				nh/=10;
			}
			//printf("!!!%d,%d\n",ansh,ansm);
			if(0<=ansm&&ansm<=m-1&&0<=ansh&&ansh<=h-1)
			{
				if(nowh<10)
				{
					printf("0%d:",nowh);
				}
				else
					printf("%d:",nowh);
				if(nowm<10)
				{
					printf("0%d\n",nowm);
				}
				else
					printf("%d\n",nowm);
				continue;
			}
		}
		for(int i=1;;i++)
		{
			if(check(nowh,nowm,i))
				break;
			
		}
	}
	
	return 0;
 } 

```

---

## 作者：Iron_Heart (赞：1)

## 思路

一道简单模拟 + 暴力。

从给定的时间开始枚举。之后判断小时数和分钟数是否合法。

判断方法具体是：

- 将它们转为字符串，如果只有一位的加上前导 $0$。
- 将每一位镜像翻转，如果无法镜像翻转则直接枚举下一个时间。
- 将字符串反转。
- 将它们的值交换，然后转为数字。
- 如果新的小时数小于 $h$ 并且分钟数小于 $m$，就打印这种方案并停止枚举。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int refl[] = {0, 1, 5, -1, -1, 2, -1, -1, 8, -1};
int t, h, m, hh, mm;

bool ok(int ho, int mi) {
    string sh = to_string(ho);
    string sm = to_string(mi);
    if (sh.size() == 1) {
        sh = "0" + sh;
    }
    if (sm.size() == 1) {
        sm = "0" + sm;
    }
    for (int i = 0; i < sh.size(); ++i) {
        if (refl[sh[i] - '0'] == -1) {
            return 0;
        }
        sh[i] = '0' + refl[sh[i] - '0'];
    }
    for (int i = 0; i < sm.size(); ++i) {
        if (refl[sm[i] - '0'] == -1) {
            return 0;
        }
        sm[i] = '0' + refl[sm[i] - '0'];
    }
    reverse(sm.begin(), sm.end());
    reverse(sh.begin(), sh.end());
    stringstream sa(sm), sb(sh);
    sa >> ho;
    sb >> mi;
    return ho < h && mi < m;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &h, &m);
        scanf("%d:%d", &hh, &mm);
        while (1) {
            if (mm == m) {
                mm = 0;
                ++hh;
            }
            if (hh == h) {
                hh = 0;
            }
            if (ok(hh, mm)) {
                printf("%02d:%02d\n", hh, mm);
                break;
            }
            ++mm;
        }
    }
    return 0;
}
```


---

## 作者：冰糖鸽子 (赞：0)

这场提交代码页面总上不去导致我一个没交差评

----

比较细节的题。考虑无脑枚举时间，再判断这个时间是否符合题目要求即可。

为了方便可以定义一个 `To` 数组，记录每个数字翻转过去的数字是什么样子。（不是数字就是 $-1$）

判断是否符合要求时，看一下现在的四个数是不是都可以合法翻转，在看反转后的两个时间有没有超出范围即可。

注意翻转之后，时的分会互换。

剩下的就是很多 `%10` 和 `/10` 了（取第一位第二位）

代码：

```cpp

// Problem: B. Planet Lapituletti
// Contest: Codeforces - Codeforces Round #705 (Div. 2)
// URL: https://codeforces.ml/contest/1493/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define A(x) (x-'0')
int T,h,m,H,M,NH,NM;//分别是数据组数,时间范围(h,m),枚举的时间(H,M),翻转过来的时间(NH,NM),
int To[20]={0,1,5,-1,-1,2,-1,-1,8,-1};//每个数翻过去的样子,这个自己模拟即可
string s;//读入的时间
bool check()
{
	if(To[H/10]==-1||To[H%10]==-1||To[M/10]==-1||To[M%10]==-1)
	{
		//若会有翻成奇怪样子的数字,则返回false
		return 0;
	}
	NM=10*To[H%10]+To[H/10];// *这里是NM不是NH*
	NH=10*To[M%10]+To[M/10];// *这里是NH不是NM*
	//通过To数组计算翻过来的时间
	if(NH<h&&NM<m) return 1;//若恰好在时间范围内,那这个时间就是可翻转的,返回true
	return 0;//否则不可翻转,返回flase
}
bool gonext()
{
	M++;//先过一分钟
	if(M==m){H++;M=0;}//分满了就归零进时
	if(H==h){H=0;}//时再满了就到第二天,时归零
	return 1;//这个是为了让主函数里的while的条件一直为1(不会死循环,因为至少00:00是合法的)
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>h>>m;
		cin>>s;
		H=A(s[0])*10+A(s[1]);//A的define在上面
		M=A(s[3])*10+A(s[4]);//同上
		if(H>=h||M>=m) continue;//若开始时间不合法,跳过此数据
		do
		{
			if(check())
			{
				/*下面开始弄成题目的输出格式*/
				if(H<10)cout<<0;
				cout<<H<<':';
				if(M<10)cout<<0;
				cout<<M<<endl;
				break;
			}
		}while(gonext());//每次加一分钟
	}
	return 0;
}

```

---

## 作者：Scrutiny (赞：0)

**题目大意：** 一个星球上的人一天 $h$ 小时 $m$ 分钟。给定一个时间，试确定此时间以后最近的时间 $HH:MM$，使得 $HH:MM$ 在竖直的镜中成的像的时间是有效的。


------------

容易发现，有效的时间必由数字 $0,1,2,5,8$ 组成。

由于 $1\le h,m\le 100$，我们可以枚举所有由 $0,1,2,5,8$ 组成的两位数（可以有前导 $0$）共 $25$ 个，然后依次查看每个时间是否有效。总复杂度 $O(25^2T)$，可以通过此题。

具体来说，首先需要实现一个定义域为 $\{0,1,2,5,8\}$ 的函数 $rev(x)$，表示数 $x$ 在镜中反转后的数。若 $x\in\{0,1,8\}$ 则返回本身；否则返回 $7-x$ 即可。


------------

再需要一个计算一天 $h$ 小时 $m$ 分钟情况下，两时刻间距离的函数 $dis(h,m,h_1,m_1,h_2,m_2)$：

如果 $h_1<h_2$ 或 $h_1=h_2,m_1\le m_2$，则代表 $h_1:m_1$ 时刻比 $h_2:m_2$ 时刻先出现，故返回 $(h_2-h_1)\times m+m_2-m_1$；

否则，说明 $h_1:m_1$ 时刻比 $h_2:m_2$ 时刻先后出现，故需再等一天，即 $(h-h_1+h_2)\times m+m_2-m_1$。

------------


假设当前枚举的小时是 $\overline{ab}$，分钟是 $\overline{cd}$，其中 $\overline{ab}$ 表示十位为 $a$，个位为 $b$ 的两位数。

那么，镜中的小时 $h'$ 就是原来的分钟反转的结果，即 $10\times rev(d)+rev(c)$；镜中的分钟 $m'$ 就是原来的小时反转的结果，即 $10\times rev(b)+rev(a)$。

要使这个时间有效，必须满足 $h'< h,m'<m$。那么，用 $ans$ 记录 $dis(h,m,\overline{ab},\overline{cd},h',m')$ 的最小值并打擂台即可。

需要注意的是，前导 $0$ 也得输出。对于任一数 $x$，需要输出前导 $0$ 当且仅当 $x<10$ **而非 $x\le 10$！！**（我打比赛时因为条件写错 WA 了两发 /dk）

------------

Sample Code(C++)

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,h,m,hour,minu;
int dis(int hh,int mm,int hou1,int minut1,int hou2,int minut2){
    if(hou1<hou2||(hou1==hou2&&minut1<minut2)){
        return (hou2-hou1)*mm+(minut2-minut1);
    }
    else if(hou1==hou2){
        if(minut1>minut2) return hh*mm+(minut2-minut1);
        return (minut2-minut1);
    }
    else{
        return (hh-(hou1-hou2))*mm+(minut2-minut1);
    }
}
int rev(int i){
    if(i==0||i==1||i==8)return i;
    return (7-i);
}
int cnt[25]={0,1,2,5,8,10,11,12,15,18,20,21,22,25,28,50,51,52,55,58,80,81,82,85,88},ans,ansh,ansm;
int main(){cin>>t;
    while(t--){
        scanf("%d%d",&h,&m);
        scanf("%d:%d",&hour,&minu);
        ans=10000000;
        for(auto i:cnt){
            for(auto j:cnt){
                if(i<h&&j<m&&(rev(i/10)+rev(i%10)*10)<m&&(rev(j/10)+rev(j%10)*10)<h){
                    if(ans>dis(h,m,hour,minu,i,j)){
                        ans=dis(h,m,hour,minu,i,j);
                        ansh=i,ansm=j;
                    }
                }
            }
        }
        if(ansh<10){
            printf("0");
            printf("%d:",ansh);
        }
        else{
            printf("%d:",ansh);
        }
        if(ansm<10){
            printf("0");
            printf("%d",ansm);
        }
        else{
            printf("%d",ansm);
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：water_tomato (赞：0)

## 题意

星球的一天有 $h$ 小时，每小时有 $m$ 分钟。现在给定一个当前时间，询问最近的在镜中对称之后合法的时间。

## 解析

主要是注意一些细节。首先判断最近的对称过去合法的小时，如果给出的时间的小时本身对称过去就是合法的，那么分钟就要从给出的分钟开始找，一直找到第一个合法的。否则，如果小时与给定的不一致，分钟就一定为 $0$，即输出一定为 `XX:00`。特别的，如果开始的小时就合法，分钟又找到结尾都找不到，那么分钟就只能取 $0$，这时我们发现原先确定的小时配上分钟就不合法了，因此需要将小时加一之后再重新找一次，同样的，找不到取 $0$ 即可。

代码中会写一些注释，帮助理解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,H,M,h,m;
int ansh,ansm;
int RRef[10]={0,1,5,-1,-1,2,-1,-1,8,-1};
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&H,&M);
		scanf("%d:%d",&h,&m);
		ansh=ansm=-1;
		for(int i=h;i<H;i++){
			int a=i/10,b=i%10,now;
            if(RRef[a]==-1||RRef[b]==-1) continue;
			now=RRef[b]*10+RRef[a];
			if(now<M){//注意对称过去之后小时和分钟两者位置对调
				ansh=i;break;
			}
		}//先找最近的合法小时
		if(ansh!=h) m=0;//如果小时变了，分钟取 0 即可
		for(int i=m;i<M;i++){
			int a=i/10,b=i%10,now;	
            if(RRef[a]==-1||RRef[b]==-1) continue;
			now=RRef[b]*10+RRef[a];
			if(now<H){
				ansm=i;break;
			}
		}
		if(ansm==-1){//分钟找不到，就隐含了给定的小时合法的条件
			h++;ansh=-1;//此时原小时不合法，必须加 1
			for(int i=h;i<H;i++){
				int a=i/10,b=i%10,now;
				if(RRef[a]==-1||RRef[b]==-1) continue;
				now=RRef[b]*10+RRef[a];
				if(now<M){
					ansh=i;break;
				}
			}
		}
		if(ansh<=0) printf("00");
		else if(ansh<10) printf("0%d",ansh);
		else printf("%d",ansh);
		printf(":");
		if(ansm<=0) printf("00");
		else if(ansm<10) printf("0%d",ansm);
		else printf("%d",ansm);
		printf("\n");//输出		
	}
	return 0;
}
```

---

## 作者：OranJun (赞：0)

~~CF居然会出这种恶心模拟/kk~~

## $Solution$

这道题就是问给定时间到下一天，最早的满足翻转后时间合法的时间并输出。

那么很显然想到枚举 $h*m$ 次，这样复杂度就是 $O(Thm)$ 。

每次枚举需要判断的是

- 时间能否被翻转

- 翻转后的时间是否不超过所给定范围

具体细节见代码。

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i=a;i<=b;++i)
#define rf(i,a,b) for(int i=a;i>=b;--i)
template<typename T>
inline void read(T &x){
	char c=getchar();x=0;bool f=0;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	x=f?-x:x;
}
typedef long long ll;
char s[10];
int b[10];
int h,m,hh,mm;
bool ck(int hh1,int mm1){//翻转后的时间判断合不合法
	int hh2=hh1,mm2=mm1;
	mm1=b[(hh2/10)]+b[(hh2%10)]*10;
	hh1=b[(mm2/10)]+b[(mm2%10)]*10;
	if(hh1<h&&mm1<m) return 1;
	return 0;
}
bool rev(int hh1,int mm1){
	if(~b[hh1%10]&&~b[hh1/10]&&~b[mm1%10]&&~b[mm1/10]&&ck(hh1,mm1))return 1;//先判断数字合不合法
	return 0;
}
bool check(){
	if(mm==m-1){
		if(hh==h-1)hh=0;
		else ++hh;
		mm=0;
	}
	else ++mm;//考虑进位问题
	
	if(rev(hh,mm)){//看能否翻转
		if(hh<10)printf("0");
		printf("%d:",hh);
		if(mm<10)printf("0");
		printf("%d\n",mm);
		return 1;
	}
}
void solve(){
	fr(i,0,9)b[i]=-1;
	b[0]=0;b[1]=1;b[2]=5;b[5]=2;b[8]=8;//处理翻转后的数字，不能反转的设成-1
	read(h),read(m);
	cin>>s+1;
	hh=(s[1]-'0')*10+(s[2]-'0'),mm=(s[4]-'0')*10+s[5]-'0';//将时间用整数表示
	if(rev(hh,mm)){//如果本身就可以那么直接把自己输出
		if(hh<10)printf("0");
		printf("%d:",hh);
		if(mm<10)printf("0");
		printf("%d\n",mm);
		return;
	}
	fr(i,0,h*m-1)//枚举下一天的所有时间
		if(check())return;
}
int main(){
	int T;
	read(T);
	while(T--)solve(); 
}


---

