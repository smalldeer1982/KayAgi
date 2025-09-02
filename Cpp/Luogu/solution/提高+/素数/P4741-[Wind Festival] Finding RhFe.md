# [Wind Festival] Finding RhFe

## 题目背景

$[Morning - 8:00 A.M.]$

热衷于结交老铁的$gyx$小哥哥听说了风筝节的举办，一大早就来到了现场，现在他已经迫不及待见到来玩的同学们啦~

## 题目描述

$gyx$的人格魅力是无限哒~

已知风筝节上有$N$($1\le N\le 10^6$)个同学（来玩的人真的很多），每个同学都对$gyx$有一个兴趣程度$c_i$（$ |c_i|\le 10^9$），因为$gyx$的性格特点太明显啦，不存在对$gyx$兴趣程度为$0$的同学，对于每个同学，都可以和$gyx$结交为老铁，$gyx$的高兴程度就是所有结！交！过！成为老铁的同学对$gyx$兴趣程度之和。$gyx$不愿意做令自己伤心的事情，所以如果所有同学对$gyx$感到反感（即兴趣程度为负）$gyx$就会直接离开风筝节。

$gyx$可以选择其中的$k$（$1\le k\le N$）个同学来结交，但一旦选择好，$gyx$的结交顺序就不可以变化了。

因为来风筝节的人实在是太多啦，$gyx$不愿意记住所有的老铁太长的时间，但是$gyx$的脑子里记着与越早结交的老铁的点点滴滴越多，也越难忘记，$gyx$忘记每个人的条件是当且仅当，在$gyx$还记着的老铁里当前的这个老铁是最后结交的。

但是由于$gyx$希望与更多不同性格的同学结交，$gyx$与每一个同学只愿意结交一次，即使遗忘以后也不会再次结交。

当风筝节上$gyx$选择的同学都结交结束后，随着时间的流逝，$gyx$也会渐渐地把所有同学都忘掉，遗忘方式与之前相同，直到最后忘记了自己结交过的所有老铁，再出发前往新的征程。

由于不同的交友并遗忘的顺序可能会发生有趣的事情，$gyx$想知道在保证自己高兴程度最大时选择好结交范围和结交顺序的情况下，$gyx$可以有多少种不同的交友并遗忘的顺序呢？

由于来风筝节的人实在是太多了，$gyx$只想知道不同顺序的方案数的值对$P$（$0<P\le 10^9$）取模后的结果。

## 说明/提示

对于$30\%$的数据保证$1\le N\le 30$；

对于$70\%$的数据保证$1\le N\le 500$；

对于$100\%$的数据保证$1\le N\le 10^6$，$0<P\le 10^9$，$|c_i|\le 10^9$。


## 样例 #1

### 输入

```
8 65
-1
36
21
97
-65
17
1
43```

### 输出

```
2```

# 题解

## 作者：nitrobenzene (赞：2)

 蒟蒻第一篇题解。。。
 这道题，根据题意，此人会和所有好感度为正数的人结交。设有n人好感度为正数，而此人忘记好友的方式为后进先出，符合栈的特点，所以方式数为第n个卡塔兰数$\frac{C_{2n}^n}{n+1}$.
 
由于p不一定是质数，所以Lucas定理不能用，我们统计各个素因子在卡塔兰数中出现的幂次。注意到：在n！中，素因子p幂次为$\sum_{i=1}^{+\infty}{[\frac{n}{p^i}]}$.
 
 ```cpp
 
 #include<set>////////
 #include<map>////////
 #include<cmath>//////
 #include<ctime>//////
 #include<queue>//////
 #include<stack>//////
 #include<cctype>///// 
 #include<cstdio>/////
 #include<vector>/////
 #include<string>/////
 #include<cstring>////
 #include<sstream>////
 #include<iostream>///
 #include<algorithm>//
using namespace std;//
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define ul unsigned long long
#define ll long long
const ll maxn=2001000;
bool vis[2001010];//是否是质数
vector<ll> p;//所有的质数
void init(){//筛质数
    ll n=maxn;
    memset(vis,1,sizeof(vis));
    vis[1]=0;
    vis[2]=1;
    p.push_back(2); 
    for(int i=4;i<=n;i+=2) vis[i]=0;
    for(ll i=3;i*i<=n;i+=2){
        if(vis[i]){
        	
            for(ll j=i*i;j<=n;j+=i) vis[j]=0;
        }
    }
    for(int i=3;i<=maxn;i+=2){
    	if(vis[i]) p.push_back(i); 
	}
	p.push_back(maxn); //防止后面过程中数组越界（反正最后2n是小于这个“质数”的，无影响）
}
int alpha[maxn]={0};//katalan数中各质数的幂次
void add_alpha_fact(int n){//阶乘素因子加成
	for(int i=0;p[i]<=n;i++){
		int res=n;
		while(res>0){
			res/=p[i];
			alpha[i]+=res;
		}
	}
}
void sub_twice_alpha_fact(int n){//阶乘素因子双倍减少
	for(int i=0;p[i]<=n;i++){
		int res=n;
		while(res>0){
			res/=p[i];
			alpha[i]-=(res+res);
		}
	}
}
void sub_alpha(int n){//单个数素因子减少
	for(int i=0;p[i]<=n;i++){
		while(n%p[i]==0){
			n/=p[i];
			alpha[i]--;
		}
	}
}
void katalan(int n){
	add_alpha_fact(2*n);//分子2n的阶乘
	sub_twice_alpha_fact(n);//分母n阶乘平方
	sub_alpha(n+1);//分母n+1
}
int main(){
	init();
	int cnt,cur,n=0;
	ll ha;
	cin>>cnt>>ha;
	while(cnt--){
		scanf("%d",&cur);
		if(cur>0) n++;
	}//统计好感度为正数的人数
	if(n==0){
		cout<<"TerriblePlace";
		return 0;
	}
	katalan(n);
	ll ans=1;
	rep(i,0,p.size() -1){
		while(alpha[i]--){
			ans=(ans*p[i])%ha;
		}
	}//乘起来
	cout<<ans;
	return 0;
}

```

---

