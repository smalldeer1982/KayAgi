# Important Exam

## 题目描述

A class of students wrote a multiple-choice test.

There are $ n $ students in the class. The test had $ m $ questions, each of them had $ 5 $ possible answers (A, B, C, D or E). There is exactly one correct answer for each question. The correct answer for question $ i $ worth $ a_i $ points. Incorrect answers are graded with zero points.

The students remember what answers they gave on the exam, but they don't know what are the correct answers. They are very optimistic, so they want to know what is the maximum possible total score of all students in the class.

## 说明/提示

In the first example, one of the most optimal test answers is "ABCD", this way the total number of points will be $ 16 $ .

In the second example, one of the most optimal test answers is "CCC", this way each question will be answered by exactly one student and the total number of points is $ 5 + 4 + 12 = 21 $ .

## 样例 #1

### 输入

```
2 4
ABCD
ABCE
1 2 3 4
```

### 输出

```
16```

## 样例 #2

### 输入

```
3 3
ABC
BCD
CDE
5 4 12
```

### 输出

```
21```

# 题解

## 作者：SFWR (赞：3)

按题意输入，并贪心求出每一个问题使正确的人最多的答案即可。注意输入的技巧
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[1005][1005];
int num[1005],cnt[1005],n,m,ans;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>ch[i];
	for(int i=1;i<=m;i++)cin>>num[i];
	for(int i=0;i<m;i++)
	{
		cnt['A']=cnt['B']=cnt['C']=cnt['D']=cnt['E']=0;
		for(int j=1;j<=n;j++)cnt[ch[j][i]]++;
		ans+=(num[i+1]*(max(max(max(max(cnt['A'],cnt['B']),cnt['C']),cnt['D']),cnt['E'])));
	}
	cout<<ans;
}
```


---

## 作者：Mubuky (赞：2)

#  _**CF1201A Important Exam 题解**_ 

![](https://api.gushi.ci/all.svg)

**首先分享一下做完这道题（ _Pretest Passed_ ）的感受:**

作为CODEFORCES Div.2的A题必定非常水，我当时也是这样想，就水着做，一眼（很快）瞄到了正解做法（太水了不过热身签到很好）。

接着我们介绍下**正解思路：**

 _**For each of the question let's count the number of answers of different type. Let cnt[i][A]=The number of A answers to the i-th question. The maximum score for that answer is a[i]⋅max(cnt[i][A],cnt[i][B],cnt[i][C],cnt[i][D],cnt[i][E]). The answer is the sum of the maximum answer for the m questions.**_ 

 _**对于每个问题，让我们计算不同类型的答案的数量。让cnt[I][a]=第i个问题的答案数。该答案的最高分数为A[i]\*max（CNT[I][A]、CNT[I][B]、CNT[I][C]、CNT[I][D]、CNT[I][E]）。答案是m个问题的最大答案之和。**_ 

**思路解释：**

即：我们用类似桶排序的思想，开一个数组tong[1001][5]每读入一个字母（该学生对这道题的答案），就把它所对应的题号的对应选项，如样例：

```cpp
2 4
ABCD
ABCE
1 2 3 4
```
对于样例的第二行（ABCD），我们把每个字母（选项）所对应的tong[i][j]加一，i表示题号，j表示选项（把字母选项映射成为数字A-0,B-1,C-2,D-3,E-4），即：

```cpp
tong[1][0]++;//处理第二行第一列（A）
tong[1][1]++;//处理第二行第二列（B）
tong[1][2]++;//处理第二行第三列（C）
tong[1][3]++;//处理第二行第四列（D）
```

同理，对于样例的第三行（ABCE）：

```cpp
tong[2][0]++;//处理第三行第一列（A）
tong[2][1]++;//处理第三行第二列（B）
tong[2][2]++;//处理第三行第三列（C）
tong[2][4]++;//处理第三行第四列（E）
```
当我们所有读入完成时，即tong数组处理完毕，我们只需遍历
```cpp
tong[i][j]（j=0;j<5;j++）
```
求出每一道题选择人数最多的选项即可（运用一个小贪心思想）

最后用每道题的答对分数乘每道题的最多答对人数（即上段所求）求和，最终的和即为答案。

### 为什么会想到运用 _小桶排+小贪心_ 的思路呢？

**桶排条件：** 这道题数据范围很小，1000的题目数，答案也只有5个（ABCDE），开数组不会炸，遍历不会TLE。这道题只是运用了桶排的部分思想，求出5个数中的最大值。

**贪心条件：** 每一个子问题间不会相互影响，即若我在第一题选A，则我第一题的答案并不会对第二题造成任何影响。且在读题后我们不难发现，所求的**总分最大值=每道题的总分最大值之和**，满足贪心策略必须具备的**无后效性**（即某个状态以前的过程不会影响以后的状态，只与当前状态有关）。而对于求每道题的总分最大值，我们知道每道题的**每道题的总分最大值=每道题的一人答对分数\*每道题的最大答对人数**，每道题的一人答对分数是题目给定的，故**只要满足每道题的答对人数最大，就可以保证每道题的总分最大**，进而回推取得总分最大，完成题目要求。

**总结：**

很好的入门题目，完成语言学习后进阶基础算法的垫脚石，学习贪心的入门样例题目。

**我的程序：**

```cpp
#include<cstdio>
#define max(a,b) a>b?a:b
int tong[1001][5];
int main()
{
	int n,m;
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;
			scanf("%c",&ch);
			tong[j][ch-'A'+1]++;
		}
		getchar();
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		int a;
		scanf("%d",&a);
		int ans=0;
		for(int j=1;j<=5;j++){
			ans=max(ans,tong[i][j]);
		}
		sum+=ans*a;
	}
	printf("%d",sum);
	return 0;
}
```

 _为满足某些朋友的需求，特提供标程如下_ 

**标程：**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m;
string s[1005];
ll a[1005];
ll ans;
ll b[1005][5];
ll ma;
int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    for (ll i=1; i<=n; i++)
    {
        cin>>s[i];
    }
    for (ll i=0; i<m; i++)
    {
        cin>>a[i];
    }
    for (ll i=0; i<m; i++)
    {
        ma=0;
        for (ll j=1; j<=n; j++)
        {
            b[i][s[j][i]-'A']++;
        }
        for (ll j=0; j<5; j++)
        {
            ma=max(ma, b[i][j]);
        }
        ans+=ma*a[i];
    }
    cout<<ans;
}
```

另外吐槽一下，今天凌晨这场Div.2，欢乐ABC做起来还以为是Div.3，做到D题有点炸，看到E就想骂人...对于E和E2（Div.2中的Div.1？）...佩服!!

 _**Name:** [Codeforces Round #577 (Div. 2)](https://codeforces.com/contest/1201)_ 

 _**Writers:** [SPatrik](https://codeforces.com/profile/SPatrik)_ 

 _**Start:** Aug/05/2019 00:35 UTC+8_ 

 _**Length** 02:00_ 

##  _**By Mubuky**_ 


---

## 作者：Waaifu_D (赞：1)

~~输入顺序我第一次居然搞反了~~

这题我觉得算不上贪心，应该算是一个模拟，求出每个题最多人选的选项，乘以这题的分数，最后求出最大总分数就可以

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>//sort必备 
#include<cstdio>
#include<iostream>
#include<string.h>
using namespace std;
int n,m,ans[6],s[1005],i,j,maxx;
char p[1002][1002];//用字符数组来储存（因为不会字符串（划掉）） 
void work()
{
	for(int i=1; i<=m;i++)
	{
		memset(ans,0,sizeof(ans));//朴素的数组清0 
		for(int j=1;j<=n;j++)//一个一个判断 
		{
		if(p[j][i]=='A') ans[1]++;if(p[j][i]=='B') ans[2]++;
		if(p[j][i]=='C') ans[3]++;if(p[j][i]=='D') ans[4]++;
		if(p[j][i]=='E') ans[5]++;
		}
		sort(ans+1,ans+1+5);//求出选的最多的选项 
		maxx+=s[i]*ans[5];//加上这题的分值 （总分数） 
	}
	cout<<maxx;//直接在函数里解决
	return; 
}
int main()
{
	cin>>n>>m;
	for(i=1; i<=n;i++)
	{
		for(j=1; j<=m;j++)
		{
			cin>>p[i][j];//每个学生的答题情况 
		}
	}
	for(i=1; i<=m;i++) cin>>s[i];//输入每题分数 
	work();//开始计算 
	return 0;
}

```


---

## 作者：happybob (赞：0)

一道贪心题目，设定 ${mp_i}_ j$ 表示第 $i$ 道题目选 $j$ 的人数，$j$ 为字符类型，枚举每一个 ${mp_i}_ j(1 \le i \le m, \,\,j = A,B,C,D,E)$，取最大值并乘以 $a_i$ 即可。

所以我用的是 `unordered_map`，具体实现参见代码：[戳我](https://www.luogu.com.cn/paste/gf4bisro)。

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15574819.html)

# 题目大意

有 $n(1 \le n \le 1000)$ 个学生在考试，共有 $m(1 \le m \le 1000)$ 道单选题，每道单选题的待选项均为 $A~B~C~D~E$。

每道单选题的分值为 $a_{i}(1 \le a_{i} \le 1000)$。现在给出第 $i$ 个学生的作答 $s_{i}($ 保证 $s_{i}$ 的长度为 $m$，且每道单选题均已作答 $)$，$s_{i}$ 的第 $j$ 个字母代表学生 $i$ 在第 $j$ 个选择题的作答选项。

求 $n$ 个学生的总分的最大值是多少。

# 题目分析

我们要求总分的最大值，自然要让所有答题者每道题出现频度最高的选项成为答案。

所以我们统计一下每个学生做第 $i$ 到题时 $A,B,C,D$ 和 $E$ 出现的个数。

求出第 $i$ 道题出现次数最多的字母，选之即可。最后每道题的最大分值的和即为答案。

# 代码

```cpp
//2021/11/18

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <algorithm>

#include <cstring>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int MA=1005;

char mp[MA][MA];

int a[MA];

int n,m;

int main(void)
{
	speed_up();
	
	cin>>n>>m;
	
	for(register int i=1;i<=n;i++)
	{
		cin>>mp[i];
	}
	
	for(register int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	
	int ans(0);
	
	for(register int i=0;i<m;i++)
	{
		static int cnt[105];
		
		memset(cnt,0,sizeof(cnt));
		
		for(register int j=1;j<=n;j++)
		{
			cnt[mp[j][i]]++;
		}
		
		ans+=a[i+1]*max({cnt['A'],cnt['B'],cnt['C'],cnt['D'],cnt['E']});
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：k3v1n070828 (赞：0)

### 这道题是一个简单的贪心问题

最优解思路：让每一道题答对的人数尽量的多。

那怎么让每道题答对的人数尽量多呢？就需要求出每一道题人数最多选项了。

思路理清楚了，就珂以规划代码框架了：

需要一个人数变量$n$，题数变量$m$;

一个二维字符数组$c$：每一行记录一个学生的答题情况；

一个$score$变量，记录每道题的分值；

五个变量$A,B,C,D,E$，记录每道题选项的情况；

最后一个答案变量$ans$，记录答案。

剩下的解释都在代码里了（码风毒瘤，大佬勿喷）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//头文件
using namespace std;
int n,m;
char c[1005][1005];
int score[1005],ans;
int A,B,C,D,E;//刚才解释的那些变量
int main(){
	scanf("%d%d",&n,&m);//输入人数和题数
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];//输入每个学生的答题情况
	for(int i=1;i<=m;i++)
		scanf("%d",&score[i]);//输入每道题的分值
	for(int i=1;i<=m;i++)
	{
		int A=0,B=0,C=0,D=0,E=0;//注意：计算每道题时，五个变量都要清零
		for(int j=1;j<=n;j++)
		{
			if(c[j][i]=='A') A++;
			if(c[j][i]=='B') B++;
			if(c[j][i]=='C') C++;
			if(c[j][i]=='D') D++;
			if(c[j][i]=='E') E++;
		}//记录每个选项的人数
		ans+=score[i]*max(A,max(B,max(C,max(D,E))));//用最暴力的方式求出最多人数的选项，然后×上分值，就是这道题的最大总分值了
	}//终于算完了一道题
	printf("%d\n",ans);//最后输出最大总分值，而且养成末尾换行的好习惯
	return 0;//结束程序
}
```

好了，看完思路和代码，自己写一遍然后AC吧QwQ

下次题解见，Bye~

---

## 作者：寒鸽儿 (赞：0)

本题是一个很水的贪心。  
每道题目的得分情况相互独立。也就是说，一道题目的正确选项的选择不会影响到零一道题目的得分。  
对于每道题目选择相同最多的答案为正确，即可保证该题得分最大。又由得分情况的独立性，对每道题采取这种策略得到的解是最优的。  
```cpp
#include <iostream>

const int maxm = 1010, cs = 10;
int s[maxm][cs];

int main() {
	int n, m, ans = 0;
	std::cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			char ch;
			while(std::cin >> ch && (ch < 'A' || ch > 'E'));
			s[j][ch-'A']++;			
		}
	for(int j = 1; j <= m; j++) {
		int t, m = 0;
		std::cin >> t;
		for(int i = 1; i < 5; ++i) if(s[j][i] > s[j][m]) m = i;
		ans += t * s[j][m];
	}
	std::cout << ans << std::endl;
	return 0;
}
```

---

## 作者：Luban (赞：0)

 其实这个就是一个贪心吧，既然要求全班总分数最大，那么一道题对的人越多越好（反正每道题都是独立存在的，不需要长远考虑），既然只有5个选项，我们只需要一一统计选该选项的人的个数即可，取5个个数中的最大值，乘以该题分数。（对于这m道题中的每道题都是这样处理哒）

本题数据也比较小，所以不用担心TLE（暴力即可）

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[1005];
int a[1005],b[6];
int main()
{
	int n,m,i=1,j;
	long long ans=0;
	cin>>n>>m;
	i=1;
	while(i<=n)
	{
		cin>>s[i];
		i++;
	}
	i=1;
	while(i<=m)
	{
		cin>>a[i];
		i++;
	}
	i=1;
	while(i<=m)
	{
		memset(b,0,sizeof(b));
		int maxn=-1;
		j=1;
		while(j<=n)
		{
			b[s[j][i-1]-'A'+1]++;
			j++;
		}
		j=1;
		while(j<6)
		{
			maxn=max(maxn,b[j]);
			j++;
		}
		ans+=maxn*a[i];
		i++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：kenlig (赞：0)

CF欢乐场

思路：所有人的最大值，那么我们找人数最多的答案并且规定这个答案是对的，不就能拿到这个题的最多的分数了吗？

然后加起来就完事

Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define LL long long
#define maxn 1005
using namespace std;
int a[maxn][6],n,m,que[maxn],tot,maxx[maxn];
char c;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c;
            if(c=='A') a[j][1]++;
            if(c=='B') a[j][2]++;
            if(c=='C') a[j][3]++;
            if(c=='D') a[j][4]++;
            if(c=='E') a[j][5]++;
        }
    }
    for(int i=1;i<=m;i++){
        cin>>que[i];
    }
    for(int i=1;i<=m;i++){
        maxx[i]=max(max(max(max(a[i][1],a[i][2]),a[i][3]),a[i][4]),a[i][5]);
    }
    for(int i=1;i<=m;i++){
        tot+=maxx[i]*que[i];
    }
    cout<<tot<<endl;
    return 0;
}
```


---

