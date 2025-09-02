# History

## 题目描述

Polycarpus likes studying at school a lot and he is always diligent about his homework. Polycarpus has never had any problems with natural sciences as his great-great-grandfather was the great physicist Seinstein. On the other hand though, Polycarpus has never had an easy time with history.

Everybody knows that the World history encompasses exactly $ n $ events: the $ i $ -th event had continued from the year $ a_{i} $ to the year $ b_{i} $ inclusive ( $ a_{i}&lt;b_{i} $ ). Polycarpus easily learned the dates when each of $ n $ events started and ended (Polycarpus inherited excellent memory from his great-great-granddad). But the teacher gave him a more complicated task: Polycaprus should know when all events began and ended and he should also find out for each event whether it includes another event. Polycarpus' teacher thinks that an event $ j $ includes an event $ i $ if $ a_{j}&lt;a_{i} $ and $ b_{i}&lt;b_{j} $ . Your task is simpler: find the number of events that are included in some other event.

## 说明/提示

In the first example the fifth event is contained in the fourth. Similarly, the fourth event is contained in the third, the third — in the second and the second — in the first.

In the second example all events except the first one are contained in the first.

In the third example only one event, so the answer is 0.

## 样例 #1

### 输入

```
5
1 10
2 9
3 8
4 7
5 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 100
2 50
51 99
52 98
10 60
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
1 1000000000
```

### 输出

```
0
```

# 题解

## 作者：Zhai0915 (赞：2)

题意：有 $n$ 个不同的历史事件，问其中有多少个会被其他事件包含。
其实这道题并不复杂，因为只要开始比别人晚，结束比别人早，就一定会被包含。
因此，方法显然是：
排序！
没错，我们只需要将时间排序，然后看一下结尾是否比别人早即可。
下面是一份平凡的代码（不要抄袭！）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
int a;
cin>>a;
pair<int,int>s[100100];//使用pair储存
for(int i=0;i<a;i++)
cin>>s[i].first>>s[i].second;//输入到pair里
int last=0,ans=0;
sort(s,s+a);//排序
for(int i=0;i<a;i++)
if(s[i].second<last)
ans++;
else
last=s[i].second;//如果末尾比原来小，ans就++，否则及时更新last
cout<<ans;
return 0; //输出后华丽结尾。
}
```

---

## 作者：Air_Color5 (赞：1)

## 题目大意
给你 $N$ 个区间，求在这 $N$ 个区间中，有多少个区间是被别的区间所包含的。
## 解析
因为题目中所输入的区间是**乱序**的，如果要依次判断每一个区间的话，不是不能做，但是会比较麻烦。那么如果我们**把所有的区间进行排序**，那就会好做很多了。因为题目中说了，所有区间的两端都是不一样的（见“输入格式”），也就是说**不可能有任何两个端点重复的情况**。那么我们就可以按照所有区间的左端点进行排序，然后依次看每一个区间。这样，就保证了每一个左端点都已经被前面的左端点包含，只要关注右端点就行。 

`
sort(a,a+n);
`

用一个 $RightMax$ 变量记录右端点中的最大值，每次将**右端点的值与 $RightMax$ 进行比较**，若小于 $RightMax$ ，则说明这个区间的左右端点都是被包含的，即将记录答案的变量 $ans$ ++即可。 
```cpp
if(CurRight<RightMax)ans++;
else RightMax=CurRight;
```

那么在存储左右端点的数据的时候，因为要排序，所以不能用两个数组分开存，不然就没法达到同步。这里我用了两种方法存储，一个是用 map 对应，另一个是用 pair 对应。这里我就把两种方法都放上来，供自行参考。
## AC代码（ map ） 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bgn[100001],mx,ans;
//bgn为记录左端点的数组
//mx为右端点的最大值
//ans为答案
map<int,int> m;
int main(){
	scanf("%d",&n);           //输入
	for(int i=0;i<n;i++){
		scanf("%d",bgn+i);//输入左端点
		cin>>m[bgn[i]];   //输入右端点
	}sort(bgn,bgn+n);         //对左端点排序
	for(int i=0;i<n;i++){     //依次看每一个区间
		if(m[bgn[i]]<mx)ans++;
        //如果右端点也被包含，则又多了一个答案
		else mx=m[bgn[i]];
        //否则，将原先的mx调为这个右端点
	}printf("%d",ans);         //输出答案
	return 0;
}
``` 
## AC代码（ pair ） 
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> v;
//这里用pair来存每一组区间，集中在vector里面
int n,res,RightMax;
//res为答案
//RightMax为右端点的最大值
int main(){
	scanf("%d",&n);//输入
	for(int i=0;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);//输入一组区间
		v.push_back(make_pair(a,b));
        //打包成pair并存入vector
	}sort(v.begin(),v.end());
        //对所有区间按照左端点排序
	for(int i=0;i<n;i++){
		if(v[i].second>RightMax)
                    //如果右端点大于RightMax
    		    RightMax=v[i].second;
		else res++;
                //否则，即右端点被包含，答案+1
	}printf("%d",res);//输出答案
	return 0;
}
``` 
**代码仅供参考**

---

## 作者：__CrossBow_EXE__ (赞：0)

一道简单的结构体排序题。
# 题意

有 $n$ 个区间，请问其中有多少个区间包含着另一个区间。

# 思路
其实，这道题并不难。

第一步，先创建一个结构体，其中包含两个变量：

- $left$，记录区间的左端点
- $right$，记录区间的右端点

需要注意一点，题目中的所有区间都是**不重复**的，这也降低了此题的难度。


------------
第二步，对所有结构体进行排序。排序依据则是它们的开始时间与结束时间。代码见下：

```cpp
bool cmp(node x,node y) {
	//如果两个时间段开始时间相同，那我们肯定选择结束时间提前的那个，也就是持续时间短的那个
	if(x.left==y.left) return x.right<y.right;
	//否则肯定选择起始时间提前的那个
	return x.left<y.left;
}
```

根据以上两步，我们就能写出最终代码了。

# 代码

除了结构体和排序依据，其他的代码还是很简单的。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

//快读，加快运行速度 
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}

//定义结构体 
struct node {
	int left,right;
} a[100005];

//排序依据 
bool cmp(node x,node y) {
	//如果两个时间段开始时间相同，那我们肯定选择结束时间提前的那个，也就是持续时间短的那个
	if(x.left==y.left) return x.right<y.right;
	//否则肯定选择起始时间提前的那个
	return x.left<y.left;
}

int main() {
	
	/*
	文件读入，由于此题并不需要，所以注释掉了 
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	*/ 

	//读入结构体信息 
	int n=read();
	for(int i=1; i<=n; i++) {
		a[i].left=read();
		a[i].right=read();
	}
	
	//排序 
	sort(a+1,a+n+1,cmp);
	
	//筛选满足题意的答案 
	int tmp,ans=0;
	for(int i=1; i<=n; i++) {
		if(a[i].right<tmp) ans++;//如果被包含进去，答案增加 
		else tmp=a[i].right;//否则就去判断后两个区间 
	}
	
	cout<<ans;
	return 0;
}
```

AC 记录图片：

![](https://i.postimg.cc/wM7krJ7x/1.png)

---

## 作者：zyl0128_alpha (赞：0)

## 题意：
有 $n$ 个区域，问有多少个会被别人包含。

## 思路：
使用结构体，在里面放起始和结束时间。再给这个数组排个序。如果起始时间相同，就看哪个结束时间小，否则就看哪个起始时间小，最后统计答案即可。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
    int a;
    int b;
};
bool cmp(node a,node b){
    if(a.a==b.a){
        return a.b<b.b;
    }
    return a.a<b.a;
}
int main(){
    int n;
    cin>>n;
    node s[100100];
    for(int i=1;i<=n;i++){
        cin>>s[i].a>>s[i].b;
    }
    int l,ans=0;
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++){
if(s[i].b<l){
    ans++;
}else{
l=s[i].b;}
}
cout<<ans;
    return 0; 
}
```


---

## 作者：rain_dew (赞：0)

[原题目传送门](https://www.luogu.com.cn/problem/CF137C)

题意：给你 $n$（$n \le 10^5$）时间段，求有多少时间段被包含于其他**任意**时间段。

思路：按照开始时间点排序，保证一定按照其中一个单调顺序，我们设 $m$ 为当前最后结束时间并初始化为第一个时间段（目前能够接受的最晚时间），并进行循环。

如果属于里面（即当前小于最晚时间），记录答案，否则当前时间与最大时间段不属于完全包含关系，此时记录新的最大时间后继续下搜，最后输出答案。

见众多大佬用的是 `pair`，那我就来一个结构体做法吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
struct data{
	int a,b;
}f[100005];
bool cmp(data x,data y)
{
	if (x.a==y.a)
		return x.b>y.b;
	return x.a<y.a;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&f[i].a,&f[i].b);
	sort(f+1,f+n+1,cmp);
	m=f[1].b;
	for (int i=2;i<=n;i++)
	{
		if (m>f[i].b)
			ans++;
		else
			m=f[i].b;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 题意
有多少个区间被其他区间所包含。


------------

### 解析
直接对区间进行排序，这时候就要用到 sort。我这里用到的是 pair, 而 sort 对 pair 默认**先对 first 升序，当 first 相同时对 second 升序**，所以我们可以不用自己写排序的规则了。   
综上所述,这是一道< 普及- >的难度。


------------
代码（~~别抄~~）：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> s[100100];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>s[i].first>>s[i].second;
	int last=0,ans=0;
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
		if(s[i].second<last)
			ans++;
		else
			last=s[i].second;//如果右端点比上一个小，便可以认为被包含在上一个其中,计数器就++，否则及时更新右端点
	cout<<ans;
	return 0;
}
```

---

