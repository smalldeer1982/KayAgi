# [ABC022A] Best Body

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc022/tasks/abc022_a

高橋君は太りやすく痩せやすい体質です。そこで彼は $ N $ 日間の体重の変化量を記録してみました。

$ 1 $ 日目の高橋くんの体重は $ W $ キログラムでした。 $ i $ 日目 $ (2≦i≦N) $ の体重の変化量は $ A_i $ キログラムでした($ A_i $ は負になり得ます)。 つまり $ i-1 $ 日目の体重を $ X $ キログラムとすると、 $ i $ 日目の体重は $ X\ +\ A_i $ キログラムだったということです。

ところで、高橋君の個人的な価値観では、体重が $ S $ キログラム以上 $ T $ キログラム以下の体型が「ベストボディー」だと考えています。

体重を記録した $ N $ 日間のうち、高橋君がベストボディーであった日数を求めてください。

## 说明/提示

### Sample Explanation 1

高橋君の体重を $ 1 $ 日目から順に書き出すと $ 50,\ 60,\ 70,\ 80,\ 90 $ になります。 よって$ 2 $ 日目と $ 3 $ 日目にのみ高橋君はベストボディーだったことになります。

## 样例 #1

### 输入

```
5 60 70
50
10
10
10
10```

### 输出

```
2```

## 样例 #2

### 输入

```
5 50 100
120
-10
-20
-30
70```

### 输出

```
2```

# 题解

## 作者：蒟蒻取不来名 (赞：3)

$$QwQ$$
感觉我已经十年没交题解了

这题有几个要点
### 1.AT要换行
2.第一天（差点因为这个WA了）也要算

3.在s和t以内就行了，可以等于
```
#include<iostream>
using namespace std;
int n, s, t, w, a, i, ans;//如题，n，s，t，w分别为天数，最佳体重的最大值和最小值和初始体重
int main()
{
	cin >> n >> s >> t >> w;
	if(w >= s && w <= t) ans ++;//初始体重也要判！！！
	for(i = 0; i < n - 1; i ++)
	{
		cin >> a;//因为只要用一次a，所以不用开数组
		w += a;
		if(w >= s && w <= t) ans ++;//等于划重点
	}
	cout << ans;
	return 0;
}
```
###### 祝Ctrl+c的人听取WA声一片QwQ

---

## 作者：勘探员·引魂人 (赞：1)

**前言：我禁不住粉丝们的软磨硬泡，于是又来发题解了。在此我也抱歉停更了一段时间**

**思路：用check函数（bool类型）来判断“x<=z&&x>=y”，若符合：答案为真；否则：答案为假，每一回合都check"su,s,t"**

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<cfloat>//文件头好像多了点啊
using namespace std;
long long n,s,t,a,su,h;//定义（long long 类型）
bool check(int x,int y,int z)//定义check函数（bool类型）
{
	if(x<=z&&x>=y) return true;//若符合"x<=z&&x>=y",答案为真
	else return false;//否则答案为假
}
int main()
{
	ios::sync_with_stdio(false);//输入输出程序流（可不打）
	scanf("%lld%lld%lld",&n,&s,&t);//输入n,s,t
	for(int i=1;i<=n;i++)//1~n循环
	{
		scanf("%lld",&a);//输入每天增长的重量
		su+=a;//自身体重+=这一天增长的重量
		if(check(su,s,t)) h++;//check(su,s,t)，若答案为真，h++
	}
	cout<<h<<endl;//输出h（记得换行！记得换行！记得换行！）
	
	return 0;//结束语不写了
}
```

---

## 作者：liuyifan (赞：1)

## 简单模拟

题意已经有了,这里就不发了

按题意暴力O(n)模拟即可

注意![数据范围:](https://s1.ax1x.com/2018/10/07/iGO3If.png)

渣code:
```cpp
#include<bits/stdc++.h>//不要脸的用bits
#define ll long long.//习惯性开long long
#define reg register
using namespace std;
ll n,s,t,tm,[1000000],i,ans;//定义数组,注意数据范围
int main()
{
    scanf("%lld%lld%lld",n,s,t);
    return 0;//结束程序
    while(n--)//循环n次,可替代for(reg int i=1;i<=n;i++)
    {
		scanf("%lld",&a[++i]);//++i为先加再取值
        eg:int i=1;cout<<++i;此时输出为2
        tmp+=a[i];//统计
        if(tmp>=s&&tmp<=t)ans++;//统计答案
    }
    printf("%lld\n",ans);//输出答案,AT的题要加换行
}
```

Ps:
提交记录:(1ms256kb)
![](https://s1.ax1x.com/2018/10/07/iGOJJS.png)
# 拒绝抄袭,共建和谐洛谷

---

## 作者：Teddy·Bear (赞：0)

本蒟蒻认为此题不隐藏都对不起诸位大佬，思路很简单，每天体重加变化量，看有几天成了QAQ贴代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,s,t,ans=0,sum=0,a[1010];//初始化
int main()
{
    cin>>n>>s>>t;//读入
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];//每天总体重
        if(sum>=s&&sum<=t) 
        ans++;//计数器加加
    }
    cout<<ans;//输出
    return 0;
}
```
警告：

输出有回车！

输出有回车！！

输出有回车！！！

珍爱生命，勿抄题解！！！

谁抄我掐爆他的小脑袋！！！

洛谷最帅和最美管理就给个通过吧QWQQAQ


---

## 作者：CZQ_King (赞：0)

### ~~沙发~~

------------
思路：把每天的体重增加起来，逐个判断是否在标准体重范围内，是的话把答案加一，最后输出答案

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int u,d,w,a,n,ans;//分别为up,down,weight,add,number,ans
int main(){
	cin>>n>>d>>u;//输入number,down和up
	for(int i=0;i<n;i++){//循环number次
		cin>>a;//输入add
		w+=a;//将体重增加a
		ans+=(w>=d&&w<=u)?1:0;//懒得用if了
	}
	cout<<ans<<endl;//最后输出答案
	return 0;//结束
}
```

---

## 作者：Jinyeke (赞：0)

### 题目：比利想在$N$天内记录体重变化，他认为体重范围在$S$到$T$内是最佳体重。现在给出他$N$天的体重：第一天给出体重$w$，之后每天的变化量为$a_i$。现求他在几天内体重为最佳体重。
#### 以下为代码（pascal）
```pascal
var
 x,i,j,s,n,k,y,a:longint;
begin
 readln(n,k,y);
 for i:=1 to n do 
  begin
   readln(x);//输入加（减）的体重（第一天也可以算加或减的）
   a:=a+x;
   if (a>=k) and (a<=y) then inc(s);//如果在k和y以内就累加s
  end;
 writeln(s);//输出（AT大坑，换行输出！）
end.
```
### 共建文明洛谷，请勿Ctrl+C！

---

