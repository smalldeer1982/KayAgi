# Fancy Number

## 题目描述

A car number in Berland consists of exactly $ n $ digits. A number is called beautiful if it has at least $ k $ equal digits. Vasya wants to change the digits in his car's number so that the number became beautiful. To replace one of $ n $ digits Vasya has to pay the sum of money, equal to the absolute difference between the old digit and the new one.

Help Vasya: find the minimum sum of money he should pay to make the number of his car beautiful. You should also find the resulting beautiful number. If there are several such numbers, then print the lexicographically minimum one.

## 说明/提示

In the first sample replacing the second digit with an "8" costs $ |9-8|=1 $ . Replacing the fifth digit with an "8" costs the same. Replacing the sixth digit costs $ |6-8|=2 $ . As a result, Vasya will pay $ 1+1+2=4 $ for a beautiful number "888188".

The lexicographical comparison of strings is performed by the < operator in modern programming languages. The string $ x $ is lexicographically smaller than the string $ y $ , if there exists such $ i $ ( $ 1<=i<=n $ ), that $ x_{i}&lt;y_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ x_{j}=y_{j} $ . The strings compared in this problem will always have the length $ n $ .

## 样例 #1

### 输入

```
6 5
898196
```

### 输出

```
4
888188
```

## 样例 #2

### 输入

```
3 2
533
```

### 输出

```
0
533
```

## 样例 #3

### 输入

```
10 6
0001112223
```

### 输出

```
3
0000002223
```

# 题解

## 作者：dzk_QwQ (赞：16)

### 题意 

   给出车牌号码 $n$ 个数，改变其中的一些数使得有相同的 $k$ 个数，改变一次所付出的代价为两个数的差的绝对值，求最少的代价并输出字典序最小的一个。

### 思路

  首先，第一眼看到题目，很容易就想到暴力枚举，但是要怎么枚举？怎么去改变其中的数来得到最小的修改代价且字典序最小？

   这时候，贪心就为我们提供了思路。我们枚举要改成相同为 $k$ 个的那个数字，对于改变得到最小的修改代价，我们知道枚举取最小值即可，但是怎么样取最小值呢？

   我们分两种情况考虑：

   1.对于当前我们要修改的 $ a[j] $ 是往小的来修改得到 $i$，我们要从前往后来修改。

   2.对于当前我们要修改的 $a[j]$ 是往大的来修改得到 $i$，我们要从后往前来修改。

  为什么这样子可以满足字典序最小？请读者自动理解（应该还挺简单的吧？）

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 11 , M = 1e5 + 7;
int num[ N ];
char  s[ M ] , str[ M ] , Sans[ M ];
int n , k ;
int main( ){
	scanf("%d%d" , &n , &k);
	scanf("%s" , s);
	for(int i = 0 ; s[i] ; i ++) 
	 num[s[i] - '0'] ++;//原车牌出现的每个数 
	 int ans = 1e9;
	 for(int i = 0 ; i <= 9 ; i ++){//枚举我们所要求的那k个相同的数 
     int cnt = num[i] , MIN = 0 ; //cnt我们满足到k个相同的计数器，这里为在原车牌中i的个数 
       memcpy  (str , s , sizeof( s ));//初始化修改的字符串成原车牌 
       
       for(int j = 1 ; j <= 9 && cnt < k ; j ++){//当前枚举数的差的数和要修改的数的差 
       	 if(i + j < 10){//当前要修改的数要变小能得到i 
		  int sum = i + j  , id = i;//sum是我们当前暴力枚举所要找到的那个要修改的数，是确定的，id是当前暴力枚举的k个相同的数 
		  for(int temp = 0 ; temp < n && cnt < k ; temp++){ 
		  	 if(str[temp] - '0' == sum){
			   str[temp] = id + '0';//修改成i 
			   cnt ++;//总共有几个和i相同 
			   MIN += j;//更新答案 
		  }
	   }
	  }
	  //当前要修改的数要变小能得到i，与上部分类似 
	  if(i - j >= 0){
	  	 int sum = i - j , id = i;
		 for(int temp = n - 1 ; temp >= 0 && cnt < k ; temp--){//为什么倒着来？待会就知道了 
		 	 if(str[temp] - '0' == sum){
		 	 	 str[temp] = id + '0';
		 	 	 cnt ++;
		 	 	 MIN += j;
			  }
		 } 
	  }
    }
    if(MIN < ans){//修改的大小保证最小 
     ans = MIN;
     strcpy(Sans , str);
   }
    //保证字典序最小 
	 else if( MIN == ans &&strcmp( Sans , str )>0 )//注意strcmp中当Sans>str时返回的为正数而并非1  
	 strcpy( Sans , str ); 
   }
  printf("%d\n" , ans );
  printf("%s" , Sans ); 
  return 0;
} 
  
	 
```

---

## 作者：wheneveright (赞：7)

### 本题解核心思想：排序

首先肯定是要找到最小的代价，也就是输出第一行所需要的答案；

可以枚举达到 $k$ 的数字，再按照每个数字与被枚举的数字的绝对差值排序，取前 $k$ 个进行计算，这样可以轻松地把 $res$ 求出；

再记录下 $res$ 的同时可以记录下所有的可以达到 $res$ 的数字，之后需要在其中寻找最小的字典序的排列

对于每个满足 $res$ 的解法，要对其进行更改，具体过程代码中讲，然后再刷出满足的最小字典序

上代码

```cpp
# include <bits/stdc++.h>
using namespace std;

struct reader {
	template <typename Type>
	reader &operator>> (register Type &ret) {
		register int f = 1; ret = 0; register char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f=-f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret << 1) + (ret << 3) + ch - '0';
		ret *= f; return *this;
	}
}fin; //快读

int N, K, xp;
struct QDS {
	int num, id;
	bool operator < (register const QDS & P) const {
		return abs (num - xp) < abs (P.num - xp) ||
			(abs (num - xp) == abs (P.num - xp) && num > P.num) ||
			(num == P.num && (num > xp ? id < P.id : id > P.id));
	}
    /*
    这里的排序非常细节
    第一行是排当前数字 xp 与数组内元素的大小的绝对差值
    第二行是当差值相同时取元素数值大小较大的放在前面，目的是当修改大的对字典序的贡献绝对比修改小的对字典序的贡献大（想想为什么）
    第三行是观察被改的数字与 xp 之间的大小关系，目的是当被改的大于 xp 时，修改较前面的比修改较后面的贡献大，反之亦然
    举个例子：
    80000008 可以改成 00000008 或是 80000000 时
    很明显 00000008 的字典序更小，所以大改小改前面的
    23333332 可以改成 33333332 或是 23333333 时
    很明显 23333333 的字典序更小，所以小改大改后面的
    */
} A[10005], B[10005];
int res, mid, rs[15];
int R[10005];

bool cmp (register const QDS & X, register const QDS & Y) {
	return X.id < Y.id;
}	//这里排序的作用是当修改处理结束之后再按照原本的顺序重组

int main () {
	fin >> N >> K; res = 2147483641;
	for (register int i = 1; i <= N; i++) A[i].num = getchar () - '0', A[i].id = i, R[i] = 10;
	for (xp = 0; xp <= 9; xp++) {
		sort (A + 1, A + 1 + N); register int now = 0;
		for (register int i = 1; i <= K; i++) now += abs (A[i].num - xp);
		if (now < res) res = now, mid = xp;
		rs[xp] = now;
	}	//这里是刷出 res
	printf ("%d\n", res);
	for (xp = 0; xp <= 9; xp++) {
		if (rs[xp] != res) continue;
		sort (A + 1, A + 1 + N);
		for (register int i = 1; i <= N; i++) B[i] = A[i];
		for (register int i = 1; i <= K; i++) A[i].num = xp;
		sort (A + 1, A + 1 + N, cmp);
		//这里就是排序的核心代码，将其修改后复原顺序，得出当修改结束的数字是 xp 时的最优解
		bool check = false;
		for (register int i = 1; i <= N; i++) {
			if (A[i].num < R[i]) {check = true;  break;}
			if (A[i].num > R[i]) {check = false; break;}
			continue;
		}	if (check == true)
		for (register int i = 1; i <= N; i++) R[i] = A[i].num;
		//这一块是不断刷最小字典序排列，直到刷到一个最小的排列方案
		for (register int i = 1; i <= N; i++) A[i] = B[i];
		// B 数组的主要用途就是保护 A 数组不被修改
	}
	
	for (register int i = 1; i <= N; i++) putchar (R[i] + '0');
	putchar (10);
	return 0;
}
```


---

## 作者：jdsb (赞：5)

## 题意
给出$n$个数字的序列，改变其中的一些数，使得其中有至少$k$个数相同，修改的代价为两个数的绝对值之差，求出最小的修改代价和字典序最小的方案。

## 分析
看完题目，我们发现这题可以进行贪心加模拟，我们枚举要改成哪个数字，然后进行贪心。首先，我们肯定要把和我们选定的数字差值更小的先修改，其次，如果是把某个数改小，那就从头开始改，如果是把某个数改大，那就从尾开始改，这样就能保证字典序尽可能小。一些细节在代码里有讲。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+5;
int n,k,len,tot,a[N],ans=1e8,vis[11],Min,num[11];
char s[N],anss[N],str[N];
int main()
{
	cin>>n>>k>>s;
	len=strlen(s);
	for(int i=0;i<len;i++) num[s[i]-'0']++;
	for(int i=0;i<=9;i++)
	{
		int tot=num[i],sum=0;
		//memcpy就是直接将s数组赋给str数组 
		memcpy(str,s,sizeof(s));
		//枚举新数和修改的数的差 
		for(int j=1;j<=9&&tot<k;j++)
		{
			int x=i+j,y=i-j;
			//改小的情况，从头扫 
			if(x<10) 
			{
				for(int l=0;l<len&&tot<k;l++)
					if(str[l]-'0'==x)
					{
						str[l]=i+'0';
						tot++;
						sum+=j;
					}
			}
			//改大的情况，从尾扫 
			if(y>=0)
			{
				for(int l=len-1;l>=0&&tot<k;l--)
				{
					if(str[l]-'0'==y)
					{
						str[l]=i+'0';
						tot++;
						sum+=j;
					}
				}
			}
		}
		if(sum<ans)
		{
			ans=sum;
			strcpy(anss,str);
			//strcpy函数是直接进行字符数组赋值 
		}
		else
		{
			// strcmp函数用来比较两个字符串大小，如果大于返回正数，小于返回负数，等于返回0 
			if(sum==ans&&strcmp(anss,str)>0)
				strcpy(anss,str);
		}
	}
	cout<<ans<<endl<<anss;
	return 0;
}
```


---

## 作者：Astatinear (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF118C)

### 思路

**暴力枚举**

这个题目的核心思想其实就是暴力枚举，并且这个题细节特别多，要特别注意。~~我整整调了1个小时~~

就是枚举 $0$ 到 $9$，并求出使得车牌号码中有 $k$ 个枚举的数的代价是多少，如果这个代价小于以前枚举出来的最小代价，则这个代价就成为最小代价，并将方案记录下来。 如果以前的最小代价等于当前的代价，则就要注意一下字典序。

详情见代码。

### 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int a[15],q[100005],ans=0x3f3f3f3f,now[100005],now2[100005];
int flg;//flg来标记最后的答案是由1～9里面的那一个数字产生的 
int cnt[100005];//标记要改变成flg的数
struct node
{
    int id,num,w,pqr;
    bool operator <(const node &n)const//特别注意一下这里的排序规则(注意字典序)。
    {
        if(pqr<=w&&pqr<=n.w)
            return num<n.num||(num==n.num&&id<n.id);
        else if(pqr>=w&&pqr>=n.w)
            return num<n.num||(num==n.num&&id>n.id);
        else
            return num<n.num||(num==n.num&&w>n.w);
    }
}arr[100005];
char p[100005];
int main()
{
	//输入
    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
        cin>>p[i];
        q[i]=p[i]-'0';
        a[q[i]]++;//桶来标记1~9之间共有多少个数字
    }
    for(int i=0;i<=9;++i)
    {
        if(a[i]>=k)//如果不用改变数字就可以完成了
        {
            cout<<0<<endl;
            for(int i=1;i<=n;++i)
                cout<<q[i];
            return 0;
        }
        for(int j=1;j<=n;++j)
        {
            arr[j].id=j;//id表示是这个车牌号的第几个
            arr[j].w=q[j];//表示车牌号上的数值
            arr[j].num=abs(q[j]-i);//表示替换这个数字为i需要多少代价
            arr[j].pqr=i;//记录最后要改变成什么
        }
        sort(arr+1,arr+n+1);//通过排序规则进行排序
        int bj=0;//来改变为车牌号有k个i的最小代价
        for(int j=1;j<=k;++j)
        {
            bj+=arr[j].num;
        }
        if(ans>bj)//如果以前的最小代价比当前最小代价大
        {
            ans=bj;//改变最小代价
            flg=i;//最后的答案是由车牌号变成k个i产生的
            memset(cnt,0,sizeof(cnt));
            for(int j=1;j<=k;++j)
            {
                cnt[j]=arr[j].id;//记录究竟要改变那些下标上的数字为i
            }
        }
        else if(ans==bj)//如果以前的最小代价等于当前最小待机,则我们要注意字典序
        {
            bool kkk=0;//标记
            for(int j=1;j<=n;++j)
            {
            	//用一个临时调用的数字来进行操作
                now[j]=q[j];
                now2[j]=q[j];
            }
            for(int j=1;j<=k;++j)
            {
            	//通过储存下来的要改变的方案进行改变
                now[arr[j].id]=i;
                now2[cnt[j]]=flg;
            }
            for(int j=1;j<=n;++j)
            {
                if(now[j]<now2[j])//如果用i产生的最小代价的字典序更小
                {
                    kkk=1;//标记
                    break;//跳出循环
                }
                else if(now[j]>now2[j])//如果用flg产生的最小代价的字典序更小
                {
                    break;//跳出循环,无需标记
                }
            }
            if(kkk==1)//如果用i产生的最小代价的字典序更小
            {
                flg=i;//flg进行替换
                memset(cnt,0,sizeof(cnt));
                for(int j=1;j<=k;++j)
                {
                    cnt[j]=arr[j].id;//储存那些下标需要替换
                }
            }
        }
    }
    for(int i=1;i<=k;++i)
        q[cnt[i]]=flg;//进行改变
    //输出
    cout<<ans<<endl;
    for(int i=1;i<=n;++i)
        cout<<q[i];
}

```

---

## 作者：洛璟 (赞：2)

恶评紫题罢……~~但是细节还是卡了我好久~~

### Solution
看到这道题的时候第一眼大家应该都会觉得挺简单的，不就是暴力枚举吗？确实，这玩意核心思想的确是暴力枚举

然而暴力枚举也有暴力枚举の痛，比如细节……

大概思路如下：

首先枚举哪个数字为其他数应该修改成的数字 $i$，如第一个样例就是应该改为 $8$

随后枚举与这个数字相差 $j$ 的每一个数字，并计算已经修改了几个数字，以及所付出的代价。

最后就来到了本题最烦的一道工序，排字典序……

我们可以知道，如果要修改的数字 $k$ 比 $i$ 大，那么我们可以直接修改，使字典序比原来小，而若 $k<i$，那么我们应当优先修改后面的数字使字典序更小。

同时对于修改代价相同的方式，我们要把它们全部存储下来，最后按照字典序排序后输出第一个，实现的话可以用字符串，但是一定要注意的是，字符串赋值使用 push_back……不然会出现很多玄学错误（确信

对于一些细节，可以去看代码注释。
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, cn;
int qwq[110], ans = 191981000;
int a[10010], an[10010];
string s[10010], as;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    for (int i = 1;i <= n;++i)
    {
        s[i].clear();
    }
    n = read();
    k = read();
    for (int i = 1;i <= n;++i)
    {
        char c = getchar();
        a[i] = c - '0';
        qwq[a[i]]++;
    }
    for (int i = 0;i <= 9;++i)//特判不用修改
    {
        if (qwq[i] >= k)
        {
            puts("0");
            for (int j = 1;j <= n;++j)
            {
                printf("%d", a[j]);
            }
            return 0;
        }
    }
    for (int i = 0;i <= 9;++i)//枚举应该修改成哪个数字
    {
    //sum用于计算已经修改的数量，tmp计算代价
        int sum = qwq[i], tmp = 0, j, cnt = 0;
        for (j = 1;j <= 9;++j)//枚举应该修改的数字与i相差的大小
        {
            sum += qwq[i + j];
            if (sum >= k)
            {
                tmp += (k - (sum - qwq[i + j])) * j;
                break;
            }
            tmp += j * qwq[i + j];//计算代价
            sum += qwq[i - j < 0 ? 100 : i - j];//三目运算防止re
            if (sum >= k)
            {
                tmp += (k - (sum - qwq[i - j])) * j;
                break;
            }
            tmp += j * qwq[i - j < 0 ? 100 : i - j];
        }
        //由于上面的sum有可能会大于k，因此开一个cnt计算已经修改的数量
        if (ans >= tmp)
        {
            for (int t = 1;t <= n;++t)
                an[t] = a[t];
            for (int e = 1;e <= j;++e)//枚举应该修改的数字与i相差的大小
            {
                for (int t = 1;t <= n;++t)//枚举每一位
                {
                //优先处理比i大的数字
                    if (an[t] - i > 0 && an[t] - i <= e)
                    {
                        if (cnt + qwq[i] >= k) continue;
                        an[t] = i;
                        cnt++;
                    }
                }
                if (cnt + qwq[i] >= k) continue;//如果修改够了就直接退出
                for (int t = n;t >= 1;--t)
                {
                    if (i - an[t] > 0 && i - an[t] <= e)
                    {
                        if (cnt + qwq[i] >= k) continue;
                        an[t] = i;
                        cnt++;
                    }
                }
                if (cnt + qwq[i] >= k)
                    continue;
            }
            if (tmp == ans)//如果答案与当前最优相同的话
            {
                cn++;//存储进字符串中，cn代表最优答案的方案数
                for (int t = 0;t < n;++t)
                {
                    s[cn].push_back(an[t + 1] + '0');
                }
            }
            else
            {//若比原来最优解更优，则清空字符串，从头开始
                for (int t = 1;t <= cn;++t)
                {
                    s[t].clear();
                }
                cn = 1;
                for (int t = 0;t < n;++t)
                {
                    s[cn].push_back(an[t + 1] + '0');
                }
            }
            ans = tmp;
        }

    }
    printf("%d\n", ans);
    s[0] = s[1];
    for (int i = 2;i <= cn;++i)//选出字典序最小
    {
        if (s[0] > s[i])
            s[0] = s[i];
    }
    cout << s[0];
    return 0;
}
```


---

## 作者：HMZHMZHMZ (赞：1)

## 题意
给定一个长度为 $ n $ 的数列，经过操作后使数组中至少有 $ k $ 个数相同，问最小代价。

一次操作可以把一个数 $ a_i $ 变成 $ x ( 0 \leq x \leq 9 ) $ ，代价为 $  \left | a_i - x  \right | $ 。

## 思路
我们考虑枚举是哪一个数的个数 $ \geq k $ 。每一次操作优先选择与它绝对值最近的数更改，然后贪心使它绝对值最小就行了。

复杂度大约是 $ O( n ) $
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int len,k,cnt[101],del[101],ans=1e9,a[101];//cnt和a记录元素出现个数，del表示该数会被替换几次
char ch[N];
string lans;
int main(){
    scanf("%d%d",&len,&k);
    scanf("%s",ch+1);
    for(register int i=1;i<=len;++i) a[ch[i]-'0']++;
    for(register int i=0;i<=9;++i){
        for(register int j=0;j<=9;++j) cnt[j]=a[j];
        if(cnt[i]>=k){//如果有不用更改就满足条件的直接输出0和原数组
            printf("0\n");
            cout<<(ch+1);
            return 0;
        }
        int now=cnt[i],l=0,sum=0;
        memset(del,0,sizeof(del));
        while(now<k){//判断删什么
            ++l;
            if(i+l<=9&&now+cnt[i+l]>=k){
                sum+=l*(k-now);
                del[i+l]+=k-now;
                now=k;
            }else if(i+l<=9){
                now+=cnt[i+l];
                sum+=l*cnt[i+l];
                del[i+l]+=cnt[i+l];
            }
            if(i-l>=0&&now+cnt[i-l]>=k){
                sum+=l*(k-now);
                del[i-l]+=k-now;
                now=k;
            }else if(i-l>=0){
                now+=cnt[i-l];
                sum+=l*cnt[i-l];
                del[i-l]+=cnt[i-l];
            }
        }
        string str="";
        if(ans>=sum){
            for(register int j=1;j<=len;++j){//按照字典序删除数字
                if(del[ch[j]-'0']>0){
                    if(ch[j]-'0'>i) str+=char(i+'0'),del[ch[j]-'0']--;
                    else{
                        if(cnt[ch[j]-'0']>del[ch[j]-'0']) str+=ch[j];
                        else str+=char(i+'0'),del[ch[j]-'0']--;
                    }
                    cnt[ch[j]-'0']--;
                }else str+=ch[j];
            }
            if(ans>sum) ans=sum,lans=str;
            else lans=min(str,lans);
        }
    }
    cout<<ans<<endl<<lans;
    return 0;
}
```

---

## 作者：xh39 (赞：1)

## 算法

贪心,桶。

## 思路

要有相同的$k$个数,那么显然可以枚举相同哪个数(下面用$i$表示)。其他的数可以**不用变化**,因为变化只会增加代价。

由于改变任何一个数都**不会影响**其他数(即每个数的改变都**相互独立**),所以可以考虑**贪心**。

尽量选代价**尽可能小**的数来改变。因为这样可以使代价最小。

于是依次枚举绝对值为$0,1,...,8,9$的数,由于本题是$10$进制,所以可以人工造出一个枚举顺序矩阵。具体见代码```a```数组。

枚举时看每个数字出现的次数,用一个$sum$**累加**,再用一个$ans$来统计答案,具体怎么加看代码(有注释),如果$sum+count>=k(count表示当前数的数量)$,说明**已经替换**了$k$个了。于是**跳出**循环。

求出了$ans$,我们又怎么求方案呢?这个才是本题的重点。

按照以下几步执行,相信你们可以看懂的。

### ①

记录下跳出循环时的**位置**。此时我们就可以很容易知道枚举了哪些数。这时我们就对于每个字符依次判断有没有被枚举过。

如果被枚举过了,相当于贪心选出的数,对于**非跳出循环时的那个数**,就直接将其**替换**成$i$。

### ②

对于跳出循环时的那个数,由于跳出循环的条件是$sum>=k$,所以可能**不会选完全**,于是我们很容易算出要选多少个数。

假如$sum=4,k=6$,那么一定是选$k-sum=2$个数。

若$a>i(a表示跳出时枚举的数)$,则说明我们**要**替换的数比替换**完**后的数要**大**,那么替换**完**后**字典序**会变**小**,**越早替换**得到的字典序**越小**,那么**从头到尾**依次替换这个数得到的**最优**。(此句有点绕,建议自己在纸上手动模拟一下)

### ?

此时**不可能**有还有未被替换的字符了。于是我们可以直接统计**最小值**,即**与当前最小值取min**。

## 代码

注:由于有些语句被我删掉了,所以可能变量会有多余,语句可能会啰嗦。
```cpp

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int mark[1000005]; //mark为桶。
int a[15][15]={
{0,1,2,3,4,5,6,7,8,9},
{1,2,0,3,4,5,6,7,8,9},
{2,3,1,4,0,5,6,7,8,9},
{3,4,2,5,1,6,0,7,8,9},
{4,5,3,6,2,7,1,8,0,9},
{5,6,4,7,3,8,2,9,1,0},
{6,7,5,8,4,9,3,2,1,0},
{7,8,6,9,5,4,3,2,1,0},
{8,9,7,6,5,4,3,2,1,0},
{9,8,7,6,5,4,3,2,1,0},
}; //枚举顺序。其中第i行(行数从0开始)表示数字i的枚举顺序。
int kkksc03[1000005],zyl[1000005]; //kkksc03表示跳出时的a,zyl表示跳出时的那个数要选多少个。
string minstring="\0"; //minstring表示字典序最小的字符串。
int main(){
	int i,j,Min=1234567,ykb=0,sum=0,ans=0,n,k,l; //i,j,l为循环变量,Min表示最小代价,ykb为要选多少个数,sum为统计选了多少个数,ans为当前i的答案。
	cin>>n>>k;
	string s,t; //s为输入的字符串,t为临时字符串变量。
	cin>>s;
	for(i=0;s[i];i++){
		mark[s[i]-'0']++; //数字字符-'0'=int数字。
	}
	for(i=0;i<10;i++){
		ans=0;
		sum=0;
		for(j=0;j<10;j++){
			if(sum+mark[a[i][j]]>=k){
				ans+=(k-sum)*abs(a[i][j]-i); //统计答案,此时只需要选(k-sum)个,然后每一个的代价是a[i][j]-i。
				zyl[i]=k-sum;
				kkksc03[i]=a[i][j];
				break;
			}
			ans+=mark[a[i][j]]*abs(a[i][j]-i); //有mark个数,代价为绝对值。
			sum+=mark[a[i][j]];
		}
		if(ans<=Min){
			if(ans<Min){
				minstring="z\0"; //注意:现在最小代价有更新,那么以前代价大minstring就不能用了,初始化为比所有数字字符串字典序都大的字符串。
				Min=ans;
			}
			ykb=zyl[i];
			t=s; //不能直接在s上更改,否则之后就枚举不了了,于是弄一个临时变量t。
			for(j=0;t[j];j++){ //直接替换小于距离。 
				for(l=0;a[i][l]!=kkksc03[i];l++){
					if(t[j]==a[i][l]+'0'){
						t[j]=i+'0';
						break;
					}
				}
			}
			if(kkksc03[i]>i){
				for(j=0;t[j]&&ykb;j++){ //替换与结束一样的。 
					if(t[j]==kkksc03[i]+'0'){
						t[j]=i+'0';
						ykb--; //选掉一个数,ykb自减1。
					}
				}
			}else{
				for(j=n-1;j>=0&&ykb;j--){ //替换与结束一样的。 
					if(t[j]==kkksc03[i]+'0'){
						t[j]=i+'0';
						ykb--;
					}
				}
			}
			minstring=min(minstring,t);
		}
	}
	cout<<Min<<endl;
	cout<<minstring;
	return 0;
}
```
## 细节或错误算法
此题思维容易,但细节很多,稍不留神就打了假算法(我就打了2次假算法)。

首先说一个错误做法:直接将代价最小的情况下数字最小的数作为$i$。

这样做会被```22294777```给卡掉。此时最小数为$2$,那结果就是```22292777```,显然不对,答案是```22274777```。

再说一个细节。一开始我是把$a$数组置为了
```cpp
int a[15][15]={
{0,1,2,3,4,5,6,7,8,9},
{1,0,2,3,4,5,6,7,8,9},
{2,1,3,0,4,5,6,7,8,9},
{3,2,4,1,5,0,6,7,8,9},
{4,3,5,2,6,1,7,0,8,9},
{5,4,6,3,7,2,8,1,9,0},
{6,5,7,4,8,3,9,2,1,0},
{7,6,8,5,9,4,3,2,1,0},
{8,7,9,6,5,4,3,2,1,0},
{9,8,7,6,5,4,3,2,1,0},
};
```
将绝对值差相同的两个数写反了。这么做为什么不可以呢?因为如果是这样,那么小的数字就会先被替换掉,于是就得不出最小字典序了。

---

## 作者：Wsy_flying_forever (赞：0)

## 重载运算符的练手题    

### 思路  
注意到《车牌号码》即把数组的每一个数大小限定在 $10$ 个以内。毫无疑问，我们可以采用枚举最后钦定的数，那么只需按照排序的一个 $comp$ 原则找到最合适的 $k$ 个数即可。  
具体规则如下：
1. 使改变差值的绝对值尽可能的小 
2. 第一种条件差值相同时，看改变的数字是被升高了数值还是被降低了数值（为了满足字典序最小，如同一位 $2$ 变 $5$ 和 $8$ 变 $5$ ，我们更愿意选择后者）
3. 第二种条件数值变化方向一致时，我们想要更靠前的位置，即编号更小的位置改变，显然这样使字典序会更小。  

### 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e4+10;
int n,k,opt,s[maxn],ans[maxn],tmp[maxn],ansval=INT_MAX;
struct Node {
	int val;
	int id;
	bool operator <(const Node &T)const {
		if (val!=T.val) return val<T.val;
		if (s[id]>opt && s[T.id]<opt) return true;
		if (s[id]<opt && s[T.id]>opt) return false;
		if (s[id]>opt) return id<T.id;
		return id>T.id;
	}
} a[maxn];
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline bool check() {
	for (int i=1;i<=n;i++)
	    if (ans[i]!=tmp[i]) return tmp[i]<ans[i];
	return false;
}
int main() {
	n=read(),k=read();
	for (int i=1;i<=n;i++) {
		char ch=getchar();
		while (!isdigit(ch)) ch=getchar();
		s[i]=ch-48;
	}
	ans[1]=10;
	for (int i=0;i<=9;i++) {
		int sum=0;
		opt=i;
		for (int j=1;j<=n;j++) 
		    a[j]=(Node){abs(i-s[j]),j};
		sort(a+1,a+n+1);
		memcpy(tmp,s,4*n+4);
        for (int j=1;j<=k;j++) {
        	sum+=a[j].val;
        	tmp[a[j].id]=i;
		}
		if (sum<ansval || sum==ansval && check()) memcpy(ans,tmp,4*n+4),ansval=sum;
	}
	printf("%d\n",ansval);
	for (int i=1;i<=n;i++)
	    printf("%d",ans[i]);
	printf("\n");
	return 0;
} 
```



---

## 作者：_Life_ (赞：0)

### 题意
给出一长度为 $n$ 的数字序列，要求其中至少有 $k$ 个相同的数字。你可以改变序列的数字，改变一次的代价为改变前后数字之差的绝对值。要求代价、序列字典序最小。

### 题解
我们从 $0$ 到 $9$ 依次钦定一个数，将其他数字修改为钦定之数，使序列中至少有 $k$ 个钦定之数，然后计算答案取最优解。

考虑如何在钦定之数确定的情况下，求出代价、序列字典序最小的答案，联想到**贪心**，然后再想一下发现贪心能做。

排序一手，选择排序后的前 $k$ 个位置变成钦定之数（这贪心老套路了吧），想一下要怎么排序：
1. 代价不同时，按代价从小到大排序
2. 若代价相同，按数字大小从小到大排序
3. 若数字大小也相同，按数字大小是否大于等于钦定之数分类讨论：
- 数字大于等于钦定之数，按数字位置从小到大排序 
- 数字小于钦定之数，按数字位置从大到小排序

正确性读者自证不难 时间复杂度 $O(n\log n)$

### 代码
```cpp
#include<cmath>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int k,n,ans=0x3f3f3f3f,i;
string str,ansstr,tempstr;
struct node
{
	int cost,val,pos;
	bool operator <(node x)const
	{
		if(cost!=x.cost)
			return cost<x.cost;
		if(val!=x.val)
			return val>x.val;
		if(val>=i)
			return pos<x.pos;
		else
			return pos>x.pos;
	}
};
vector <node> vec;
int main()
{
	cin>>n>>k>>str;
	for(i=0;i<=9;i++)
	{
		int sum=0;
		vec.clear();
		for(int j=0;j<str.size();j++)
			vec.push_back((node){abs(str[j]-'0'-i),str[j]-'0',j});
		sort(vec.begin(),vec.end());
		tempstr=str;
		for(int j=0;j<k;j++)
			sum+=vec[j].cost,tempstr[vec[j].pos]=i+'0';
		if((sum==ans&&tempstr<ansstr)||sum<ans)
			ansstr=tempstr,ans=sum;
	}
	cout<<ans<<endl<<ansstr;
}
```

---

## 作者：Oscar12345 (赞：0)

一道简单的模拟题目，难度不大，认真思考，而且因为题目数据比较简单，所以大家可以放心的去水。

思路：枚举每个数，从每个数的两端出发，枚举每次最小付出的代价，并保存最小字典序的字串，注意一点：变大的数从后修改，变小的数从前面修改，这样又可以保证每次修改的字串是字典序最小的了，另外当原有字串相同个数大于或等于k，结果都为零，我先以为必需等一k个，想的太多了，修改后，果断A了。

代码在下面（建议自己先思考）：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
const int N=1e4+10;
int n,k;
char s[N],ss[N];
int num[19];
int cnt[19],len;
int all[N][15];
 
void solve(int x)
{
	int sum;
	for(int i=0;i<len;i++)
	{
		int e=s[i]-'0';
		if(cnt[e])
		{
			if(e>x)
			{
				cnt[e]--;
				ss[i]=x+'0';
			}
			else
			{
				if((i-1>=0&&(all[len-1][e]-all[i-1][e])<=cnt[e])||(i==0&&all[len-1][e]<=cnt[e]))
				{
					ss[i]=x+'0';
					cnt[e]--;
				}
				else
					ss[i]=s[i];
			}
		}
		else
			ss[i]=s[i];
	}
	ss[len]='\0';
}
 
char sss[N];
void solve2(int x)
{
	int sum;
	for(int i=0;i<len;i++)
	{
		int e=s[i]-'0';
		if(cnt[e])
		{
			if(e>x)
			{
				cnt[e]--;
				sss[i]=x+'0';
			}
			else
			{
				if((i-1>=0&&(all[len-1][e]-all[i-1][e])<=cnt[e])||(i==0&&all[len-1][e]<=cnt[e]))
				{
					sss[i]=x+'0';
					cnt[e]--;
				}
				else
					sss[i]=s[i];
			}
		}
		else
			sss[i]=s[i];
	}
	sss[len]='\0';
}
 
int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",s);
	len=strlen(s);
	memset(all,0,sizeof(all));
	memset(num,0,sizeof(num));
	for(int i=0;i<len;i++)
	{
		int x=s[i]-'0';
		if(i==0)
			all[i][x]=1;
		else
		{
			for(int kk=0;kk<=9;kk++){
				if(kk==x)
					all[i][x]=all[i-1][x]+1;
				else
					all[i][kk]=all[i-1][kk];
			}
		}
		num[x]++;
	}
 
	int ans=0x3f3f3f3f;
	for(int i=0;i<=9;i++)
	{
		int res=0;
		int sum=num[i];
		int t=1;
		memset(cnt,0,sizeof(cnt));
		if(sum>=k)
		{
			ans=0;
			strcpy(ss,s);
			break;
		}
		while(sum<k&&(i+t<=9||i-t>=0))
		{
			if(i+t<=9)
			{
				if(num[i+t]+sum>=k)
				{
					cnt[i+t]=k-sum;
					res+=(k-sum)*t;
					if(ans>res)
					{
						solve(i);
						ans=res;
					}
					else if(ans==res)
					{
						solve2(i);
						if(strcmp(ss,sss)>0)
							strcpy(ss,sss);
					}
					sum=k;
				}
				else
				{
					res+=num[i+t]*t;
					sum+=num[i+t];
					cnt[i+t]=num[i+t];
				}
			}
			if(i-t>=0)
			{
				if(num[i-t]+sum>=k)
				{
					cnt[i-t]=k-sum;
					res+=(k-sum)*t;
					if(ans>res)
					{
						solve(i);
						ans=res;
					}
					sum=k;
				}
				else
				{
					res+=num[i-t]*t;
					sum+=num[i-t];
					cnt[i-t]=num[i-t];
				}
			}
			t++;
		}
	}
	printf("%d\n",ans);
	printf("%s\n",ss);
	return 0;
}

```

---

## 作者：wangjunze (赞：0)

这道题我想了很多方法，最后还是贪心对我有些启发，你只需要枚举字符串中出现过的数字来当标准（比如第一个样例，8就是标准）数据十分水

上代码
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	string s;
	cin>>n>>m;
	cin>>s;
	string pre=s;
	string t="";
	string comp="9999999999999999";
	int ans=99999999;
	for(char i='0';i<='9';i++)
	{
		int cnt=0;
		for(int j=0;j<s.size();j++)
		{
			if(s[j]==i)
				cnt++;
			if(cnt==m)
			{
				cout<<"0"<<endl;
				cout<<s;
				return 0;
			}
		}
	}
	for(int i=0;i<s.size();i++)
	{
		if(t.find(s[i])==string::npos)
			t+=s[i];
	}
	for(int i=0;i<t.size();i++)
	{
		int hurt=0;
		int cnt=0;
		for(int j=0;j<s.size();j++)
		{
			if(s[j]==t[i])
				cnt++;
		}
		int k=1;
		bool type=0;
		for(;;)
		{
			for(int j=0;j<s.size();j++)
			{
				if(abs((int)(t[i]-'0')-(int)(s[j]-'0'))==k)
				{
					s[j]=t[i];
					cnt++;
					if(cnt==m)type=1;;
					hurt+=k;
				}
			}
			k++;
			if(type)
				break;
		}
		if(s<comp && hurt<ans)
		{
			comp=s;
			ans=hurt;
		}
		s=pre;
	}
	cout<<ans<<endl;
	cout<<comp<<endl;
    return 0;
}

```


---

