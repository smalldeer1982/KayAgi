# 成績判定

## 题目描述

[problemUrl]: https://atcoder.jp/contests/qupc2014/tasks/qupc2014_a

あなたはある試験の採点者です。 この試験ではいくつかの科目が存在し、その科目のうち、既定の数の科目に合格すると、試験に合格できます。 この試験では合格人数が初めからきめられているため、科目の合格点を採点結果を見て調整しなければなりません。 調整は面倒なので、採点結果を入力すると合格点を表示するプログラムを作ることにしました。また、科目ごとに調整するのは面倒なので、すべておなじです。 合格人数が最低合格人数以上になる、最大の合格点を出力してください。 ある科目で合格するとは、獲得した点数が、合格点以上になることとします。 入力は以下の形式で与えられる。

> $ A $ $ B $ $ C $ $ D $ $ E_{(0,0)} $ ・・・・$ E_{(0,A-1)} $ ・ ・ ・ ・ $ E_{(C-1,0)} $ ・・・・$ E_{(C-1,A-1)} $

 科目数$ A $、 合格に必要な科目数$ B $、 人数$ C $、 最低合格人数$ D $、 また得点の表$ E_{(i,j)} $ $ E_{(i,j)} $は$ i $番目の人の、$ j $番目の科目についての得点である。 入力中は各変数はすべて整数である。また、以下の制約を満たす。 - $ 2≦A,C≦10 $
- $ 1≦B≦A $
- $ 1≦D≦C $
- $ 0≦E_{(i,j)}≦100 $
 
 調整した点数を整数１行で出力してください ```
<pre class="prettyprint linenums">
4 3 3 2
10 15 25 30
5 20 20 30
40 100 100 100
```

 ```
<pre class="prettyprint linenums">
20
```

# 题解

## 作者：MZY666 (赞：8)

吐槽：为什么我每次交AT的题都会中一次 `无限Waiting` 的奖，好神奇啊（

[原题传送门](https://www.luogu.com.cn/problem/AT858)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-at858)。

### 【 题意概括 】

又忍不住吐槽一下：这题原来的翻译有些过于简洁了吧，都无法推断输入的是什么。

给大家理一下：

输入将会以以下形式给出。

科目数 $a$，合格所需科目数 $b$，人数 $c$，最低合格人数 $d$ 以及得分表 $e_{i,j}$ 。

其中 $e_{i,j}$ 是第 $i$ 个人关于第 $j$ 个科目的得分。

求：合格人数为 最低合格人数及以上时 最大合格的分数 是多少。

### 【 思路 】

直接做嘛。

我们可以先对每一组 $e_i$ 进行排序，以求出每个学生要达到合格要求的 最大的合格分 各是多少。

将上述结果存储到一个名为 $maxi$ 的一维数组里面。

随后再对 $maxi$ 的元素进行排序，就可以得出满足题意的最大合格分数了。

来，是时候看看完整代码了。这样才好说清。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件可好 
using namespace std;
int e[15],maxi[15];
int main(){//主函数 
	int a,b,c,d,i,j;//i,j为循环变量
	scanf("%d%d%d%d",&a,&b,&c,&d);//输入
	for(i=1;i<=c;i++){
		for(j=1;j<=a;j++)scanf("%d",&e[j]);//输入此学生的成绩
		sort(e+1,e+a+1);//排序
		maxi[i]=e[a-b+1];
		//随后求出这个学生想要达到合格要求时的最大的合格分是多少
	}
	sort(maxi+1,maxi+c+1);//再对所有期望合格分进行排序
	printf("%d\n",maxi[c-d+1]);//第c-d+1项即为符合题意的最大合格分。
	return 0;//over~
}
```

最后，由于作者自愿禁言了，如果有建议请私信。否则将**无法**回复您哦！

完结撒花~（疯狂暗示 $-w-$

---

## 作者：MarchKid_Joe (赞：2)

# “水”~~无脑~~模拟暴力枚举算法
## 1. 题意
- 有 a 个科目， c 个人。并且一个人要及格需要 b 个科目分数大于等于所输出的结果（即符合要求的最大分数线），还要保证有 d 个人几个。
- 题目中有一点不严谨“某门科目合格是指获得的分数**大于**及格分数”，但实际通过样例来看，是大于等于。

## 2. 思路
看到了数据范围0≦E(i,j)≦100，不难想到从100开始往0枚举，当枚举符合条件的数时，就输出（因为是**从大到小**枚举，所以第一个符合条件的分数线一定是最大的）。
## 3. 代码
```cpp
#include<cstdio>
using namespace std;
int a,b,c,d,s [15][15],tot,ans;
int main()
{
	scanf("%d%d%d%d",& a,& b,& c,& d);
	for(int i = 1;i <= c;i ++)
	 for(int j = 1;j <= a;j ++)
	 scanf("%d",& s[i][j]);//输入 
	for(int i = 100;i >= 0;i --)//枚举分数 
	{
		ans = 0;//存储及格的人数 
		for(int j = 1;j <= c;j ++)//枚举人数 
		{
			tot = 0;//存储某个人及格科目的个数 
			for(int k = 1;k <= a;k ++)//枚举某个人的各科目分数 
			 if(s [j][k] >= i) ++ tot;//本科及格tot+1 
			if(tot >= b) ++ ans;//及格科目>=b个时，ans+1 
		}
		if(ans >= d)//及格的人数符合>=d人时，立即输出答案结束程序 
		{
			printf ("%d\n",i);//记得"\n"; 
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：学霸壹号 (赞：2)

## 翻译
### 题目描述
这道题原来翻译的有点烂哈~这里写一个简单点的翻译。
你是一位老师。学校有一个规则：学生们考试时，只要有B门科目的成绩比分数线高或“卡在线上”就算OK了。但是这个考试OK的人数（D）被可恶的校长固定了，~~也就是说，总有点人OK不了~~，但是这个可恶的校长又脑子不好，不知道如果想让OK的人数大于等于D的话，那么制定的分数线应该是多少。于是请到了你这位又会编程又敬业的老师，让你编一个程序，输出这条难算的分数线。~~其实不难，就是枚举~~
### 输入格式
```
A B C D E
E[0][0] E[0][1] ... E[0][A-1]
E[1][0] E[1][1] ... E[1][A-1]

***

E[C-1][0] E[C-1][1] ... E[C-1][A-1]
```
A：科目数 B：上面解释过 C：总人数 D：前面也解释过，~~仔细看！~~
### 输出格式
```
Answer
```
### 样例数据
没什么问题
### 数据范围
$2≦A,C≦10$

$1≦B≦A$

$1≦D≦C$

$0≦E[i][j]≦100$
## 有点害怕吗？
**没关系，我们还是来分析**

## 数据分析中
人数：**少**

科目数：**少**

分数：**$0-100$算个啥啊？早就被咱们荒废了。**
## 结论
算法：**枚举**

算法详细描述：**for循环暴力枚举，才$100$，$0-100$自在得很！**

难度：**入门难度**

## 部分代码（C++）
```cpp
for(int s=100;s>=0;--s){
	int sum;
	int tot=0;
	for(int i=0;i<c;++i){
		sum=0;
		for(int j=0;j<a;++j)
			if(e[i][j]>=s)
				++sum;
		if(sum>=b)
			++tot;
	}
	if(tot>=d){
		cout<<s<<endl;
		break;
	}
}
```
完整代码：**不给**

---
看我干嘛？没了！

---
你干嘛啊？

---
找代码啊？

---
告诉你了，没有！

---
╮(╯-╰)╭无奈，干嘛浪费时间？

---
[好吧，](https://www.luogu.org/paste/iu4cgg0u)[我这](https://www.luogu.org/paste/ewmxzs7w)[就给](https://www.luogu.org/paste/8lo2adkl)[你。]( https://www.luogu.org/paste/w1pzjlwa)
**注意，这里有许多冒牌代码，当心！**

---

## 作者：Edmundino (赞：1)

# 题意

就是有$C$行$A$列个数

每一行的数有$B$个达到一个值（你要求的数）时，就算过关

但是过关的行数不能超过$D$

所以要你求符合条件的最大达标值

# 分析

题目要求每行有$B$个值达标时才算过关

因为达标值是有个一成不变的值啊

所以其实就是说你这行数第$B$大的数

是否到了达标值

这样我们就很好的转化了

再看过关的行数不能超过$D$

我们知道判断一行是否过关就要看这行第$B$大的数

所以我们就要把每一行第$B$大的数收集起来

接着从大到小排序

求出第$D$大的数

这就是我们要求的达标值了

# 代码

### 如何从大到小排序

我的方法是：$sort+cmp$

这是最简单的方法

其实$sort$函数的语法是还有个$cmp$的

这是来定义排序方式的

但是有时你可以不写，这就默认是升序排序了

但这题我们要使用降序，所以要启用$cmp$

$sort$函数进行排序的时间复杂度为$O(n  log2n)$

见代码

```cpp
bool cmp(const int x,const int y)
{
	return x>y;
 } 
```

### 最后送上完整AC代码

###### 还有记得最后打换行哦

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

const int N=20;

int a,b,c,d,e[N],q[N],top;

bool cmp(const int x,const int y)
{
	return x>y;
 } 

int main()
{
	cin>>a>>b>>c>>d;
	for(int i=1;i<=c;i++)
	{
		for(int j=1;j<=a;j++)
		{
			cin>>e[j];
		}
		sort(e+1,e+1+a,cmp);
		q[++top]=e[b];
	}
	sort(q+1,q+1+top,cmp);
	cout<< q[d]<<endl;
	return 0;
}
```


---

## 作者：灼眼的夏娜 (赞：1)

我的全身心都败给了这道智障题。。。。。。

首先，当我衬出了我目前所学的那点儿小破日语把这题翻译完了之后，鼠标向

下一滑，就看到了**题目翻译**这四个大字......mmp

看完题当我还在疑惑这题是为啥会被评为绿的时候，~~就把代码敲完了~~，交上去

全WA—_—，为啥呢？在我疑惑不解的时候于是点开了题解，发现这题**必须**注意

是必须输出换行......这破题，再扯一句，做这道题是因为这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/59rky0ii.png)

单纯看它不顺眼而已，emmm，扯多了，还是要说题的

题目要求分数线尽量高些，那就找一个分数，让所有人刚好卡过，显然我们

可以把每一个人的分数$sort$一下，取第$B$大的那个分数作为他的基准分，

要让$D$个人合格，那可以再把这些基准分排一遍，取第$D$大的就行了，代码只

有两个$sort$，记得最后打换行，提醒你咯
```cpp
#include<bits/stdc++.h>
#define R register

using namespace std;
int A, B, C, D;
int v[15], b[15];

int main() {
	cin>>A>>B>>C>>D;
	for(R int i = 1;i <= C;++ i) {
		for(R int j = 1;j <= A;++ j) cin>>v[j];
		sort(v + 1, v + A + 1);
		b[i] = v[A - B + 1];
	}
	sort(b + 1, b + C + 1);
	cout<<b[C - D + 1]<<endl;
	return 0;
}
```


---

## 作者：艾恩葛朗特 (赞：1)

这道题题解不是很多，我来写一篇*^__^*

这是一道简单的
## 贪心

首先把每个人分数第b高的数（即选这个人最高需要的分数）记录进s数组中
```cpp
	for (int i=1;i<=c;i++){
		for (int j=1;j<=a;j++)
			scanf("%d",&val[j]);
		sort(val+1,val+a+1);
		s[i]=val[a-b+1];
	}
```
然后找出s数组中第d高的分数（即c人中选d人最高的分数）
```cpp
	sort(s+1,s+c+1);
	printf("%d\n",s[c-d+1]);
```
最后附上完整代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a,b,c,d,s[15],val[15];
int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	for (int i=1;i<=c;i++){
		for (int j=1;j<=a;j++)
			scanf("%d",&val[j]);
		sort(val+1,val+a+1);
		s[i]=val[a-b+1];
	}
	sort(s+1,s+c+1);
	printf("%d\n",s[c-d+1]);
	return 0;
}
```
~~我才不会告诉你我是因为没换行才WA了5次呢~~

---

## 作者：EuphoricStar (赞：0)

## 题意

$A$ 个科目，$C$ 个人，$B$ 为每人至少及格的科目数，$D$ 为最低及格人数，得分表 $E_{(i,\,j)}$ 为第 $i$ 个人第 $j$ 个科目的分数。

求及格人数为最低及格人数及以上的最大及格分数。

## 思路

此题就是一道模拟加排序的~~大水~~题。

首先对每个人的分数进行**降序**排序，那么第 $i$ 个人的最大及格分数为 $E_{(i,\,B)}$，将这个分数保存至数组 `ans` 中。

最后对 `ans` 进行降序排序，$ans_D$ 即为最终答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, c, d, e[15], ans[15];

int main()
{
    ios::sync_with_stdio(0); // 优化 cin, cout
    cin >> a >> b >> c >> d;
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < a; ++j) cin >> e[j];
        sort(e, e + a, greater<int>()); // greater<int>() 表示降序排序
        ans[i] = e[b - 1];
    }
    sort(ans, ans + c, greater<int>());
    cout << ans[d - 1] << endl; // 记得换行
    return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

# Description  
现在有 $a$ 门科目，$c$ 个人。每个人必须通过 $b$ 门科目才算及格，而至少需要 $d$ 个人及格。现在给出成绩表 $e_{i,j}$ 表示第 $i$ 个人在第 $j$ 门科目的得分。  
（由于题目翻译太没用了，所以本蒟蒻自己翻译了一边，希望各位巨佬能看懂~）  
# Solution  
看见题目的第一个反应就是**排序**，对于每一个人，我们把他的成绩降序排序后他的**期望及格分**就是 $e_{i,b}$ 。我们存下每一个 $e_{i,b}$ 并对其继续做一遍**降序排序**，记这一次存下来的数列存在 p 里，那么 $p_d$ 即为所求。  
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int f[N],p[N];	//对于每一组e，我们可以将其降维至一组数据f中
int a,b,c,d;
int ans;

bool cmp(int u,int v) {	//注意是降序
	return u > v;
}

int main() {
	scanf("%d %d %d %d",&a,&b,&c,&d);
	for(int i = 1;i <= c;i++) {
		for(int j = 1;j <= a;j++) {
			scanf("%d",&f[j]);
		}
		sort(f + 1,f + a + 1,cmp);
		p[i] = f[b];
	}
	sort(p + 1,p + c + 1,cmp);
	printf("%d\n",p[d]);
	return 0;
}
```

---

