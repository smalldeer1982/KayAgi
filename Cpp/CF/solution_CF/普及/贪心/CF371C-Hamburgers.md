# Hamburgers

## 题目描述

Polycarpus loves hamburgers very much. He especially adores the hamburgers he makes with his own hands. Polycarpus thinks that there are only three decent ingredients to make hamburgers from: a bread, sausage and cheese. He writes down the recipe of his favorite "Le Hamburger de Polycarpus" as a string of letters 'B' (bread), 'S' (sausage) и 'C' (cheese). The ingredients in the recipe go from bottom to top, for example, recipe "ВSCBS" represents the hamburger where the ingredients go from bottom to top as bread, sausage, cheese, bread and sausage again.

Polycarpus has $ n_{b} $ pieces of bread, $ n_{s} $ pieces of sausage and $ n_{c} $ pieces of cheese in the kitchen. Besides, the shop nearby has all three ingredients, the prices are $ p_{b} $ rubles for a piece of bread, $ p_{s} $ for a piece of sausage and $ p_{c} $ for a piece of cheese.

Polycarpus has $ r $ rubles and he is ready to shop on them. What maximum number of hamburgers can he cook? You can assume that Polycarpus cannot break or slice any of the pieces of bread, sausage or cheese. Besides, the shop has an unlimited number of pieces of each ingredient.

## 样例 #1

### 输入

```
BBBSSC
6 4 1
1 2 3
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
BBC
1 10 1
1 10 1
21
```

### 输出

```
7
```

## 样例 #3

### 输入

```
BSC
1 1 1
1 1 3
1000000000000
```

### 输出

```
200000000001
```

# 题解

## 作者：da32s1da (赞：5)

由于需要的材料和已经有的材料均不超过100，所以可以考虑暴力枚举前100次。100次后已经有的材料（如果有用）均用完，所以只能买材料，然后就O(1)算了

```
#include<cstdio>
#include<cstring>
typedef long long LL;
const int N=105;
char S[N];
int len,nb,ns,nc,pb,ps,pc,b,s,c;
LL r,Ans;
int main(){
	scanf("%s%d%d%d%d%d%d%I64d",S,&nb,&ns,&nc,&pb,&ps,&pc,&r);
	len=strlen(S);
	for(int i=0;i<len;i++)
	if(S[i]=='B')b++;
	else if(S[i]=='S')s++;
	else if(S[i]=='C')c++;
	for(int i=1;i<=100;i++){
		if(nb>=b&&ns>=s&&nc>=c){
			nb-=b;ns-=s;nc-=c;
			Ans++;continue;
            //材料够用
		}
		if(nb<b)r-=(b-nb)*pb,nb=b;
		if(ns<s)r-=(s-ns)*ps,ns=s;
		if(nc<c)r-=(c-nc)*pc,nc=c;
        //买材料
		if(r>=0)Ans++,nb-=b,ns-=s,nc-=c;
		else break;
        //钱不够直接break
	}
	printf("%I64d\n",Ans+(r>0)*r/(b*pb+s*ps+c*pc));
    //有钱的话，买材料
}
```

---

## 作者：tomhzl (赞：4)

### 用三个变量记录要用多少原材料
### 二分做多少个汉堡即可
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;


long long b,c,s,nb,nc,ns,pb,pc,ps,money;//原材料需求、当前量、价格、和钱
bool check(long long mid){//检查函数
    long long n=0;//需要的总钱数
    if(mid*b>nb)n+=(mid*b-nb)*pb;//买面包的钱
    if(mid*s>ns)n+=(mid*s-ns)*ps;//买香肠的钱
    if(mid*c>nc)n+=(mid*c-nc)*pc;//买芝士的钱
    return n<=money;//三种花费加在一起和本来有的钱比较
}
int main() {
    char a[110];
    cin>>a+1;//下标从一开始的字符串读入
    long long len=strlen(a+1);
    cin>>nb>>ns>>nc;
    cin>>pb>>ps>>pc;
    cin>>money;
    for(long long i=1;i<=len;i++){
        if(a[i]=='B')b++;//面包数
        else if(a[i]=='C')c++;//芝士数
        else s++；//香肠数
    }
    long long l=0,r=money+max(nb,max(nc,ns));//初始边界
    while(l<=r){//喜闻乐见的二分
        long long mid=l+r>>1;//>>1等于/2
        if(check(mid)){//检查能不能做mid个汉堡
            l=mid+1;//能做mid个汉堡就有可能可以做更多汉堡
        }
        else r=mid-1;//连mid个汉堡都做不了只能往少考虑
    }
    printf("%lld",r);//输出
    return 0;//功德圆满
}
```

---

## 作者：灵光一闪 (赞：3)

## ~~二分答案一时爽，一测数据火葬场…~~

## 十年OI一场空，不开longlong见祖宗

~~↑真对……~~

这道题是一道二分答案的例题( •̀ ω •́ )

然鹅……![](https://cdn.luogu.com.cn/upload/image_hosting/act85tci.png)

10min later…… 20min later…… 1day later……


你能理解我的感受吗qaq

代码：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
string str;
int main(){
	cin>>str;
	long long need[3]={0};
	long long b,s,c;
	long long B,S,C;
	long long money;
	cin>>b>>s>>c>>B>>S>>C>>money;
	for(long long i=0;i<str.size();i++){
		if(str[i]=='B'){
			need[0]++;
		}
		else if(str[i]=='S'){
			need[1]++;
		}
		else{
			need[2]++;
		}
	}
//cout<<need[0]<<" "<<need[1]<<" "<<need[2]<<endl;
//cout<<"error"<<max((8*need[0]*B-b),(long long)0)+max((8*need[1]*S-s),(long long)0)+max((8*need[2]*C-c),(long long)0)<<endl;
	long long low=0;
	long long high=money*100;
	long long mid=0;
	while(high>low){
//cout<<mid<<" "<<high<<" "<<low<<endl;
		mid=(low+high+1)/2;
		if(max((mid*need[0]*B-b),(long long)0)+max((mid*need[1]*S-s),(long long)0)+max((mid*need[2]*C-c),(long long)0)>money){
			high=mid-1;
		}
		else{
			low=mid+1;
		}
	}
	cout<<high<<endl;
	return 0;
}
```

**这份代码并不能AC**_~~duckling~~

交了Wrong Answer别找窝qaq

上面的那个二分写挂惹qaq

## 所以有人能帮我DEBUG一下吗？

二分不行（其实是我太弱了调不出二分qaq），那么这个如何AC呢？

其实这个思路很简单，就是先把已经有的全部用完，然后再利用C++自带的下取整算出能“买”多少个汉堡

code:
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
int ans;
string str;
int main(){
	cin>>str;
	long long need[3]={0};//需要的（BSC）
	long long b,s,c;//现有的
	long long B,S,C;//市场价
	long long money;
	cin>>b>>s>>c>>B>>S>>C>>money;
	for(long long i=0;i<str.size();i++){//先处理出来BSC各需要多少个
		if(str[i]=='B'){
			need[0]++;
		}
		else if(str[i]=='S'){
			need[1]++;
		}
		else{
			need[2]++;
		}
	}
	for(int i=0;i<926;i++){//9.26某位dalao的生日（这里大于100即可，因为数据范围只有100，但是别给整个爆int的数啊，不然unAC了后果自负……）
		if(b>=need[0]&&s>=need[1]&&c>=need[2]){//不需要购买其他物品
			b-=need[0];
			s-=need[1];
			c-=need[2];
			ans++;
		}
		else{
			int plan=(max(need[0]-b,(long long)0)*B+max(need[1]-s,(long long)0)*S+max(need[2]-c,(long long)0)*C);//计划再购买一个需要多少钱
			if(plan>money){//没钱就可以跳出去了
				break;
			}
			else{//
				ans++;//又能做一个汉堡
				money-=plan;//先把钱减掉
			}
			b-=need[0];//再把东西减掉
			s-=need[1];
			c-=need[2];
			b=max(b,(long long)0);//全部弄成非负数
			s=max(s,(long long)0);
			c=max(c,(long long)0);
		}
//cout<<b<<" "<<s<<" "<<c<<" "<<ans<<" "<<money<<endl;
	}
	cout<<ans+money/(need[0]*B+need[1]*S+need[2]*C)<<endl;//ans是目前能做的，然后后面的很明显能看出是剩下的钱能“买”多少蛋糕
	return 0;
}
```

The End.

---

## 作者：tallnut (赞：1)

# 思路
答案显然具有单调性，考虑**二分答案**。设定二分下界为 $0$（因为题目中说若无解输出 $0$），上界为 $10^{13}$（比 $10^{12}$ 再大一点）。

而 check() 函数就可以直接**贪心**，如果现有的材料数量足够就不动用资金，否则就用 $(cnt_i \times x - n_i) \times p_i$ 块钱（其中 $cnt_i$ 表示第 $i$ 种调料的数量）。$cnt_i \times x - n_i$ 表示需要买的份数。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/138290335)。
```
#include <iostream>
using namespace std;
string s;
int cnt[3];
int n[3];
int p[3];
long long l,r,mid,ans;
long long money,tmpmoney;
long long max(long long a,long long b) { return a > b ? a : b; }
bool check(long long x)
{
	tmpmoney = money;
	for (int i = 0;i < 3;i++)
	{
		if (tmpmoney < (max(cnt[i] * x - n[i],0) * p[i])) return false;
		tmpmoney -= (max(cnt[i] * x - n[i],0) * p[i]);
	}
	return true;
}
int main()
{
	cin >> s;
	for (int i = 0;i < s.size();i++)
		if (s[i] == 'B') cnt[0]++;
		else if (s[i] == 'S') cnt[1]++;
		else cnt[2]++;
	cin >> n[0] >> n[1] >> n[2] >> p[0] >> p[1] >> p[2] >> money;
	l = 0;
	r = 1e13;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
		{
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	cout << ans;
}
```

---

## 作者：wanghanjun (赞：1)

这种题明显是二分答案。。。

求出三种材料需要的个数，对于每个汉堡数k，求出至少要花多少钱才能满足做出k个汉堡。

然后再对答案进行二分就行了。。。

```cpp
#include <iostream>
using namespace std;

typedef long long ll;
ll pb,pc,ps,nb,ns,nc,ans;
ll l=0,r,b=0,s=0,c=0,p,mid;
const int MAXN=101;
char a[MAXN];

bool check(ll t){
	ll res=0;
	if(t*b>=nb) res=res+(t*b-nb)*pb;
	if(t*c>=nc) res=res+(t*c-nc)*pc;
	if(t*s>=ns) res=res+(t*s-ns)*ps;
	return res<=p;
}//判断每个汉堡数是否可行

int main(){
	cin>>a;
	for(int i=0;a[i];i++){
		if(a[i]=='B') b++;
		if(a[i]=='C') c++;
		if(a[i]=='S') s++;
	}//统计
	cin>>nb>>ns>>nc;
	cin>>pb>>ps>>pc;
	cin>>p;
	r=2000000000000;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)==true){
			ans=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}//二分答案
	cout<<ans<<endl;
	return 0;
}
//10211314334486875731~~~
```


---

## 作者：封禁用户 (赞：0)

这题我们发现可以枚举材料为用完之前，后来用完了全靠卖直接算就可以了，毕竟数据范围中材料需求和材料已有都很小，但是我们拥有的钱却极大。

接着我们再来特判一下材料要不要用，这道二分答案题就能迎刃而解了！

code

```cpp
#include <bits/stdc++.h>// 头文件
using namespace std;// 使用命名空间
string s;
long long B,S,C,B$,S$,C$,bs=0,ss=0,cs=0,m;//温馨提示：十年OI一场空，不开long long见祖宗
bool check(long long x){// 判断钱是否足够买配料
	long long sum=0;
	if(x*bs>B)sum+=(x*bs-B)*B$;
    if(x*ss>S)sum+=(x*ss-S)*S$;
	if(x*cs>C)sum+=(x*cs-C)*C$;
    return sum<=m;  
}
long long b_s(long long l,long long r){// 二分答案
    long long ans=0;
    while(l<=r){
        long long mid=(l+r)/2;
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }
        else r=mid-1;
    }
    return ans;
}
int main(){
    cin>>s;
    cin>>B>>S>>C;
    cin>>B$>>S$>>C$;
    cin>>m;
    int len=s.size();
    for(int i=0;i<len;i++){// 统计每个汉堡所需配料数量
        if(s[i]=='B')bs++;
        else if(s[i]=='S')ss++;
        else cs++;
    }
    long long l=0,r=2000000000000;
    cout<<b_s(l,r);
    return 0;//华丽の结束
} 
```


感谢大家的阅读！

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现可以对最多做的汉堡数进行二分，设 $sumb$ 为还需要的 $B$ 材料，$sums$ 为还需要的 $S$ 材料，$sumc$ 为还需要的 $C$ 材料，$xb$ 为一个 $B$ 材料需要的钱数，$xs$ 为一个 $S$ 材料需要的钱数，$xc$ 为一个 $C$ 材料需要的钱数，$n$ 为你有的钱数。如果 $sumb \times xb+sums \times xs+sumc \times xc \leq n$，则将最多做的汉堡数增加，否则则减少。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int yb,ys,yc,xb,xs,xc,n,b,s,c,lb,ub=1e14,mid;
string ss;
bool check(long long int x){
	long long int sumb=max(0LL,b*x-yb),sums=max(0LL,s*x-ys),sumc=max(0LL,c*x-yc);
	return sumb*xb+sums*xs+sumc*xc<=n;
}
int main(){
	cin>>ss>>yb>>ys>>yc>>xb>>xs>>xc>>n;
	for(int i=0;i<ss.size();i++){
		if(ss[i]=='B'){
			b++;
		}
		if(ss[i]=='S'){
			s++; 
		}
		if(ss[i]=='C'){
			c++;
		}
	}
	while(ub-lb>1){
		mid=(ub+lb)/2;
		if(check(mid)){
			lb=mid;
		}
		else{
			ub=mid;
		}
	}
	cout<<lb;
	return 0;
}
```


---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

这题我们可以枚举材料为用完之前，后来用完了全靠卖直接算就可以了，毕竟数据范围中材料需求和材料已有都很小，但是我们拥有的钱却极大。 

但是您以为这就结束了吗！  

完全没有，我们都知道 CF 的网站数据是要多毒瘤，就有多毒瘤。   

然后我就被卡了，原因就是有可能有些材料根本不用！这真是坑到家了，导致如果用循环一直枚举会发现永远跳不出来，当然这种问题特判一下就好了。    

### Solution:  

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

string s;
ll n[4],a[4],v[4],r;
int main()
{
	cin>>s;
	for(int i=0;i<s.size();++i){
		if(s[i]=='B') n[1]++;
		if(s[i]=='S') n[2]++;
		if(s[i]=='C') n[3]++;
	}
	a[1]=read(),a[2]=read(),a[3]=read();
	v[1]=read(),v[2]=read(),v[3]=read();
	r=read();
	ll S=n[1]*v[1]+n[2]*v[2]+n[3]*v[3];
	ll ans=0;
	while((a[1]!=0&&n[1]!=0)||(a[2]!=0&&n[2]!=0)||(a[3]!=0&&n[3]!=0)){
		if(a[1]>=n[1]) a[1]-=n[1]; else r-=(n[1]-a[1])*v[1],a[1]=0;
		if(a[2]>=n[2]) a[2]-=n[2]; else r-=(n[2]-a[2])*v[2],a[2]=0;
		if(a[3]>=n[3]) a[3]-=n[3]; else r-=(n[3]-a[3])*v[3],a[3]=0;
		if(r<0){
			printf("%lld\n",ans);
			return 0;
		}
		++ans;
	}
	ans+=r/S;
	printf("%lld\n",ans);
	return 0;
}

```

---

