# Travel Cards

## 题目描述

In the evening Polycarp decided to analyze his today's travel expenses on public transport.

The bus system in the capital of Berland is arranged in such a way that each bus runs along the route between two stops. Each bus has no intermediate stops. So each of the buses continuously runs along the route from one stop to the other and back. There is at most one bus running between a pair of stops.

Polycarp made $ n $ trips on buses. About each trip the stop where he started the trip and the the stop where he finished are known. The trips follow in the chronological order in Polycarp's notes.

It is known that one trip on any bus costs $ a $ burles. In case when passenger makes a transshipment the cost of trip decreases to $ b $ burles ( $ b&lt;a $ ). A passenger makes a transshipment if the stop on which he boards the bus coincides with the stop where he left the previous bus. Obviously, the first trip can not be made with transshipment.

For example, if Polycarp made three consecutive trips: "BerBank" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "University", "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerMall", "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerBank", then he payed $ a+b+a=2a+b $ burles. From the BerBank he arrived to the University, where he made transshipment to the other bus and departed to the BerMall. Then he walked to the University and returned to the BerBank by bus.

Also Polycarp can buy no more than $ k $ travel cards. Each travel card costs $ f $ burles. The travel card for a single bus route makes free of charge any trip by this route (in both directions). Once purchased, a travel card can be used any number of times in any direction.

What is the smallest amount of money Polycarp could have spent today if he can buy no more than $ k $ travel cards?

## 说明/提示

In the first example Polycarp can buy travel card for the route "BerBank ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/020e46f55824918e845cf09cdcf9e4d7853d3223.png) University" and spend $ 8 $ burles. Note that his second trip "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerMall" was made after transshipment, so for this trip Polycarp payed $ 3 $ burles. So the minimum total sum equals to $ 8+3=11 $ burles.

In the second example it doesn't make sense to buy travel cards. Note that each of Polycarp trip (except the first) was made with transshipment. So the minimum total sum equals to $ 2+1+1+1=5 $ burles.

## 样例 #1

### 输入

```
3 5 3 1 8
BerBank University
University BerMall
University BerBank
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4 2 1 300 1000
a A
A aa
aa AA
AA a
```

### 输出

```
5
```

# 题解

## 作者：xzggzh1 (赞：3)

题意：

有 $n$ 次旅行计划，一次单程旅行的车费为 $a$，代表从下车的地方上车再到另一个地点的花费为 $b$，

有特价券 $k$ 张价格为 $f$ 的特价券。特价券可以使一条 $a↔b$ 路线变成免费的，给一个旅游路线。求最小的花费。 

---

按照题意模拟每一条路线上的花费，然后排序，优先对花费多的路线使用特价券。

题目中给的使站点的名字，可以直接用 `string` 存然后丢到 `map ` 里就好了。

---

核心代码：

```cpp
int n,a,b,k,f,ans=0,x;
string s[333][2];vector<int>v;
bool cmp(int x,int y){return x>y;}
map<string,int>mp;map<string,int>::iterator it;
void add(int x,string s1,string s2){
    if (s1>s2) swap(s1,s2);
    s1+=s2;mp[s1]+=x;ans+=x;
}
int main(){
    cin>>n>>a>>b>>k>>f;
    for (int i=1;i<=n;i++){
        cin>>s[i][0]>>s[i][1];
        if (i==1||s[i][0]!=s[i-1][1])add(a,s[i][0],s[i][1]);
        else add(b,s[i][0],s[i][1]);
    }
    for (it=mp.begin();it!=mp.end();it++){
        x=it->second;
        if (x>f) v.push_back(x-f);
    }
    sort(v.begin(),v.end(),cmp);
    for (int i=0;i<min(k,(int)v.size());i++)ans-=v[i];
    cout<<ans;
}
```




---

## 作者：Jin_Yichen (赞：0)

# 洛谷CF847K题解
### [题目传送门](https://www.luogu.com.cn/problem/CF847K)
## 题意
有 $n$ 次旅行计划，一次单程旅行的车费为 $a$ ，代表从下车的地方上车再到另一个地点的花费为 $b$ ，有 $k$ 张价格为 $f$ 的特价券。特价券可以使一条 $a↔b$ 路线变成免费的。给一个旅游路线，求最小的花费。~~（原题摘抄不过分吧）~~
## 分析
我们可以模拟整个旅行的过程，接着把花费按从大到小排序，优先对花费最多的路线使用优惠券。

当然，我们不需要对站点进行编号，只需要把这个名字作为唯一量进行模拟即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,k,f,ans,t;//nabkf见题目，ans为答案，t为缓存
string str[305][2];//输入数据
vector<int> vec;
bool cmp(int x,int y){return x>y;}//sort比较函数
map<string,int> mp;
map<string,int>::iterator iter;//迭代器
void addway(int a,string s1,string s2){
	if(s1>s2)swap(s1,s2);
	s1+=s2,mp[s1]+=a,ans+=a;
}
int main(){
	scanf("%d%d%d%d%d",&n,&a,&b,&k,&f);//输入
	for(int i=1;i<=n;i++){
		cin>>str[i][0]>>str[i][1];//输入
		if(i==1||str[i][0]!=str[i-1][1])
			addway(a,str[i][0],str[i][1]);//增加路线
		else addway(b,str[i][0],str[i][1]);
	}
	for(iter=mp.begin();iter!=mp.end();iter++){//迭代路线（模拟）
		t=iter->second;
		if(t>f)vec.push_back(t-f);
	}
	sort(vec.begin(),vec.end(),cmp);//排序花费
	for(int i=0;i<min(k,(int)vec.size());i++)ans-=vec[i];//计算花费
	printf("%d",ans);
	return 0;
}
```

---

