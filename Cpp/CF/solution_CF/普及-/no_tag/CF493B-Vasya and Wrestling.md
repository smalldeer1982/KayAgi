# Vasya and Wrestling

## 题目描述

Vasya has become interested in wrestling. In wrestling wrestlers use techniques for which they are awarded points by judges. The wrestler who gets the most points wins.

When the numbers of points of both wrestlers are equal, the wrestler whose sequence of points is lexicographically greater, wins.

If the sequences of the awarded points coincide, the wrestler who performed the last technique wins. Your task is to determine which wrestler won.

## 说明/提示

Vasya has become interested in wrestling. In wrestling wrestlers use techniques for which they are awarded points by judges. The wrestler who gets the most points wins.

When the numbers of points of both wrestlers are equal, the wrestler whose sequence of points is lexicographically greater, wins.

If the sequences of the awarded points coincide, the wrestler who performed the last technique wins. Your task is to determine which wrestler won.

## 样例 #1

### 输入

```
5
1
2
-3
-4
3
```

### 输出

```
second
```

## 样例 #2

### 输入

```
3
-1
-2
3
```

### 输出

```
first
```

## 样例 #3

### 输入

```
2
4
-4
```

### 输出

```
second
```

# 题解

## 作者：liuzhongrui (赞：3)

~~貌似代码还可以再短点。~~

## 思路

由于数据分正负，但与正负的大小无关，因此，我们可以用向量来刻画正负。

创建一个包含两个向量的数组 $v$，其中 $v_0$ 用于存储第一名摔跤手的得分，而 $v_1$ 用于存储第二名摔跤手的得分，可以使用动态数组实现：

```
vector<int> v[2];
```

然后我们可以遍历每一轮比赛，获取每轮比赛的得分 $x$。根据得分的正负将得分存入相应的向量，并更新该向量的总分，在每个向量的末尾添加一个标记，值为 $1$。

最后比较两个摔跤手总分的结果，如果第一名摔跤手的总分大于第二名，输出 ```first```，否则输出 ```second```。

## Code

~~十分精巧而凝练。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x;
signed main() {
	scanf("%lld",&n);
	vector<int> v[2];
	for(int i=0; i<n; i++) {
		scanf("%lld",&x);
		v[x>0].push_back(abs(x));
		v[x>0][0]+=abs(x);
	}
	v[x>0].push_back(1);
	printf("%s",(v[1]>v[0]?"first":"second"));
	return 0;
}
```


---

## 作者：Kawaii_qiuw (赞：1)

### 题意

给出 $n$ 个 techniques，每个 technique 的值为 $a_i$。$a_i > 0$ 表示把这个分数给第一个 wrestler，$a_i < 0$ 表示给第二个 wrestler。约定 $a_i \ne 0$。

### 思路

- 如果两个人最终的得分不相等，分数多的那个人获胜。

- 如果两个人最终的得分相等，可以分两种情况讨论：

1. 序列中至少有一位不相等，那么字典序大的那个获胜。例如第一个人：$1,4,5,8$，第二个人：$2,3,6,7$，总和都为 $18$。那么第二个人胜。

1. 序列中每位都相等，那么最后得分的那个人获胜。例如给出的 $n$ 个数为 $4$ 那么第一个人获胜。

备注：由于 RemoteJudge 暂不可用，所以没有 AC 记录。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef __int64 LL;
const int maxn = 2e5 + 5;
int a[maxn], b[maxn];
LL sum;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif // ONLINE_JUDGE

    int n, in;
    while (scanf("%d", &n) != EOF) {
        sum = 0;
        int mark;
        int l1 = 0, l2 = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d", &in);
            sum += in;
            if (in > 0) {
                a[l1++] = in;
                mark = 1;
            }
            else {
                b[l2++] = -in;
                mark = 2;
            }
        }
        //最终的得分不相等
        if (sum > 0)
            printf("first\n");
        else if (sum < 0)
            printf("second\n");
        //最终的得分相等
        else {
            int flag = 0;
            //两条得分序列中至少有一位不相等
            for (int i = 0; i < l1 && i < l2; i++) {
                if (a[i] > b[i]) {
                    flag = 1;
                    break;
                }
                else if (a[i] < b[i]) {
                    flag = 2;
                    break;
                }
            }
            // 两条得分序列相等时，最后得分的那个人获胜
            if (!flag) {
                if (l1 == l2)
                    printf("%s\n", mark == 1 ? "first" : "second");
            }
            //得分序列不相等
            else        
                printf("%s\n", flag == 1 ? "first" : "second");
        }
    }
    return 0;
}
```

完结撒花。

---

## 作者：Stone_Xz (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF493B)

### 题目分析：

 - 给你 $n$ 个数，如果第 $i$ 个数是正数，就是属于选手一的。如果是负数，就是属于选手二的。按给定规则比较，输出分数大的一方。

这道题是一道简单的模拟：

1. **直接比较选手一和选手二的总分数。**

> 如果是选手一的分数，直接累加到他的总分数去。是选手二的话，累加的应该是 ```abs(num)```，两个总分直接比较即可。

2. **如果总分数相等，比较两人分数的字典序。**

> 按顺序记录下两个选手的每个得分，组成两个序列 $a$ 和 $b$。如样例二中，选手一就是 ```3```，选手二就是 ```12```。然后从头开始逐位比较，一旦发现 $a[i] > b[i]$，选手一获胜，反之同理。

3. **总分数和字典序都相同，最后一个输入的分数是属于谁的，谁就大。**

> 记录最后一个输入的分数是属于谁的，直接看即可。

 - 注意 $n$ 的范围应该是 $n \le 200000$。

## AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, a[N], b[N], cnt_a, cnt_b, sum_1, sum_2, e;

signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int num;
		cin >> num;
		if(num > 0){
			a[++cnt_a] = num;
			sum_1 += num;
			e = 1;             // 记录最后一个 
		}
		else{
			b[++cnt_b] = -num; // -num 跟 abs(num) 此处的功能一样 
			sum_2 += -num;
			e = 2;
		}
	}
	if(sum_1 > sum_2)          // 1. 直接比较 
		cout << "first";
	else if(sum_1 < sum_2)
		cout << "second";
	else
	{
		// 2. 字典序比较 
		for(int i = 1; i <= min(cnt_a, cnt_b); i++) // 循环到 min(cnt_a, cnt_b) 即可 
			if(a[i] > b[i]){
				cout << "first";
				return 0;
			}
			else if(a[i] < b[i]){
				cout << "second";
				return 0;
			}
		if(e == 1)                             // 3. 最后的得分是谁拿的 
			cout << "first";
		else
			cout << "second";
	}
	return 0;
}
```

---

## 作者：volatile (赞：1)

~~好久没写题解了~~

# 思路

统计两个选手的分数，如果不是相同的就直接比大小，否则按字典序的大小，注意这里的字典序是两个选手的分数拼起来，比如样例 $1$

```
5
1
2
-3
-4
3
```

那么两个选手分别是 `123` 和 `34`。如果字典序相同，就看最后一个得分的选手是谁谁就赢。

# 代码

```cpp
#include<iostream>
using namespace std;
const int MAXN=200005;
long long a[MAXN],b[MAXN];
int main()
{
    int n,ai=0,bi=0,last;//last是最后一个选手是谁
    long long as=0,bs=0;//忘记开longlong了T_T
    cin>>n;
    for(int i=1;i<=n;i++){
        long long x;
        cin>>x;
        if(x>0){
            ai++;
            a[ai]=x;
            as+=x;
        }
        else{
            bi++;
            b[bi]=-x;
            bs-=x;
        }
        if(i==n){
            if(x>0) last=1;
            else last=0;
        }
    }
    if(as>bs) cout<<"first";//判断总分数
    else if(as<bs) cout<<"second";
    else{
        for(int i=1;i<=min(ai,bi);i++){//判断字典序
            if(a[i]>b[i]){
                cout<<"first";
                return 0;
            }
            else if(a[i]<b[i]){
                cout<<"second";
                return 0;
            }
        }
        if(ai>bi) cout<<"first";
        else if(ai<bi) cout<<"second";
        else if(last) cout<<"first";//判断最后一个选手
        else cout<<"second";
    }
    return 0;
}
```


---

## 作者：lihl (赞：0)

### 题意
令 $\operatorname{cmp}(x,y)$ 表示比较 $x$ 与 $y$ 的大小。

给定 $n$ 个数，令 $s=t=0$，若 $a_i>0$ 则 $s\gets s+a_i$，若 $a_i<0$ 则 $t\gets t-a_i$，求 $\operatorname{cmp}(s,t)$。保证 $\lvert a_i \rvert \le 10^9$。

特别地，若 $s=t$，则记 $S_i$ 为第 $i$ 个对 $s$ 产生贡献的值，记 $T_i$ 为第 $i$ 个对 $t$ 产生贡献的值，求 $\operatorname{cmp}(S_i,T_i)$。若 $\forall i,1\le i \le \frac{n}{2},S_i=T_i$，则判断 $a_n\in S$ 还是 $a_n \in T$。
### 分析
由题意，不难发现我们可以维护两个和 $s$ 和 $t$ 和两个数组 $S$ 和 $T$，读入时再多维护 $a_n\in S$ 还是 $a_i\in T$ 即可，是一道简单的模拟题。

代码略。

---

## 作者：Autumn_Dream (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF493B)

**思路：**

直接模拟题意。定义两个变量 $sum_1,sum_2$ 来储存每次加减的情况，再用两个队列 $q_1,q_2$ 来处理字典序。

先读入，对于每次读入一个数 $x$ 时：
- $x>0$，讲 $sum_1$ 加上 $x$，然后把 $x$ 压入队列 $q_1$；
- $x<0$，讲 $sum_2$ 加上 $-x$，然后把 $-x$ 压入队列 $q_2$。

接下来判断是否能从分数上必出谁获胜。

然后就是处理字典序，每次判断队首的大小，不相等则得分大方获胜，直到有一队列为空。

最后再看最后读入的 $x$ 是第几位选手的得分即可。

[Code](https://www.luogu.com.cn/paste/pnpioom5)

---

## 作者：__Immorta__ (赞：0)

**前言：**

挺好的模拟呢。。建议评橙。

**注意：**

本片代码需要 c++14 及以上的编译器。

具体代码部分：
```c 
to_string(awa)
```
含义为将整数转换为字符串。

**题目大意：**

两个人，进行比赛。

输入 $n$ 个数，如果是正数则是第一位选手的得分，负数则是第二位选手的得分。

- 如果第一位选手分数大则获胜，输出 `first`，否则输出 `second`。
- 若分数相同则按得分的字典序比大小，字典序大的获胜。
3.若字典序相同则最后一位得分的选手获胜。

**代码详解：**

个体头文件方面：
```c
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
```

我们可以首先读取表演的次数，然后读取每次表演的得分。它将正数得分累加到第一位选手的总分中，负数得分累加到第二位选手的总分中。如果总分不同，则直接输出获胜者。如果总分相同，则比较两个选手得分的字典序。如果字典序也相同，则检查最后一位得分的选手，输出获胜者。


根据题意来看，首先输入 $n$ 代表表演的次数。

接下来 $n$ 个数，如果是正数则是第一位选手的得分，负数则是第二位选手的得分。

由此我们可以列出代码：

```c
vector<int> mp;
string a,b;
for(int i=1;i<=n;i++){
  int m;
  cin>>m;
  mp.push_back(m);
  if(m>0) {
    a+=to_string(m)+" ";
  }
  else{
    b+=to_string(-m)+" ";
  }
}
int sum=0,num=0;
for(int awa : mp) {
  if(awa>0){
    sum+=awa;
  } 
  else {
    num+=-awa;
  }
}
```

最后就是判断输出的部分了，这道题真的有黄吗？挺简单的。。

- 如果第一位选手分数大则获胜，输出 `first`，否则输出 `second`。
```c
if(sum>num){
  cout<<"first"<<endl;
}
else if(num>sum){
  cout<<"second"<<endl;
}
```
- 若分数相同则按得分的字典序比大小，字典序大的获胜。

- 若字典序相同则最后一位得分的选手获胜。

```c
else{
    if(a>b){
        cout<<"first"<<endl;
    }
	else if(b>a) {
        cout<<"second"<<endl;
    }
	else{
        if(mp.back()>0){
            cout<<"first"<<endl;
        }
		else{
            cout<<"second"<<endl;
        }
    }
}
```

----

完结撒欢 ★°:.☆(￣▽￣):.°★

---

## 作者：TiAmo_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF493B)


---

## 思路：
这道题个人认为挺简单的，先是简单判断累加每个人的分数，再按照题意模拟即可。

注意：累加第二个人的分数时记得加绝对值，因为是负数。

---

## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define pre(i, a, b) for(int i = (a); i >= (b); i--)//无关紧要的东西，懒人必备

const int N = 1e6 + 10;

int sum1[200005], sum2[200005], a, b;//sum1存储第一个人的分数，sum2存储第二个人的分数，用于后面字典序的比较，a,b是sum1和sum2的长度

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, s1 = 0, s2 = 0, size;
	cin >> n;
	
	rep(i, 1, n){
		int t;
		cin >> t;
		
		if(t >= 0){
			s1 += t;
			sum1[++a] = t;
			size = 1;//若t>=0说明是第一个人的，s1累加分数，sum1存储分数，size表示最后一个得分的人，若是1，最后得分的人就第一个人
		}
		else{
			s2 += abs(t);
			sum2[++b] = abs(t);
			size = 2;//若t<0说明是第二个人的，s2累加分数，sum2存储分数，size与上面同理
		}
	}
	
	if(s1 > s2){
		cout << "first";//直接判断
	} 
	else if(s1 < s2){
		cout << "second"; 
	} 
	else{//如果总分相同
		rep(i, 1, min(a, b)){
			if(sum1[i] > sum2[i]){
				cout << "first"; 
				return 0;
			}//判断字典序大小
			else if(sum1[i] < sum2[i]){
				cout << "second"; 
				return 0;
			}
		}
		
		if(size == 1){//若字典序相同，判断最后一个得分的人是谁
			cout << "first";
		} 
		else{
			cout << "second"; 
		}
	}
	
	
	return 0;
}

```

---

## 作者：ht__QAQ__ (赞：0)

## 思路：
一道简单的模拟题目。首先，统计选手分数，再判断哪个选手分数多。如果相同的话，就进入下一个环节。接下来进行字典序比较，选择得分次数较小的进行循环即可。最后，如果字典序都相同的话，那么，谁是最后一个得分的，谁就获胜。**注意**，题面上并未标注数据范围，$n$ 的数据范围是 $n \le 2\times 10^{5}$。

## 代码：

```cpp
#include<bits/stdc++.h>//偏奇怪的码风 
#define int long long
using namespace std;
const int N=200005;//被数组大小坑惨了 
int n,a[N],x=0,y=0,q[N],w[N],s1=1,s2=1;
/*--------
x:一号的得分
y:二号的得分
q 与 w 数组: 计算字典序用的 
s1 与 s2:两个人分别有多少次得分 
--------*/
signed main(){
	scanf("%lld",&n);// #define int long long 之后记得写 %lld 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]>0) //统计一号得分 
			x+=abs(a[i]),
			q[s1]=abs(a[i]),
			s1++;
		if(a[i]<0) //统计二号得分 注意绝对值 
			y+=abs(a[i]),
			w[s2]=abs(a[i]),
			s2++; 
	}
	if(x>y) //一号比二号分多 
		puts("first"),
		exit(0);// 同 return 0; 
	else if(y>x) //二号比一号分多
		puts("second"),
		exit(0);
	else{
		for(int i=1;i<=min(s1,s2)/*按最小的比即可*/;i++){
			if(q[i]>w[i]) //比较字典序
				puts("first"),
				exit(0);
			else if(q[i]<w[i])
				puts("second"),
				exit(0);
		}
		if(a[n]<0) //谁是最后得分的 
			puts("second");
		else 
			puts("first");
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：0)

## 前言
看到楼上大佬的一堆``if else``，蒟蒻不禁瑟瑟发抖。

这题其实~~是个淼题~~思维含量比较低，~~有手就行~~但比较考验代码能力。、

本蒟蒻的代码可能比较精简~~就24行~~，可能比较容易理解

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF493B)

题目翻译中已经给了大致题意，但是要重新申明的一点是，这里的“字典序”指的是将两人的每一次操作分别按输入顺序存起来，然后比较字典序。

## 分析
这题很显然要维护两个数组对应两个人，将每次操作存入数组中，累加每个人的和与操作长度，接下来就是判断了。

1. 首先，比较总和，我用的是 ```s``` 数组。
2. 其次，如果总和一样，将操作数组 ```a``` 逐位比较，一旦不同，直接返回（比较字典序）。
3. 再次，如果还未返回，那么比较操作长度（比较字典序）。
4. 最后，如果依旧一样，那么返回最后一次操作对应的人。

本蒟蒻用了函数的方式进行比较，具体的到代码里理解吧。

## AC_Code
~~~
#include<bits/stdc++.h>
#define int long long//累加数组会炸int
using namespace std;
const int maxn=12900001;
int n,x,l[29],s[29],a[maxn][2];//l为操作长度，s为操作和，a记录每一次操作
bool judge(){
	if(s[0]!=s[1]) return s[0]<s[1];//比较总和
	for(int i=1;i<=min(l[0],l[1]);i++)//逐位比较操作，注意长度取min
	 if(a[i][0]!=a[i][1])
     return a[i][0]<a[i][1];
	if(l[0]==l[1]) return x<0;//长度一样看最后一次操作，注意x要是全局变量
	else return l[0]<l[1];//否则比较长度
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		a[++l[(x<0)]][(x<0)]=abs(x);//第二坐标0表示第一个人，1表示第二个
		s[x<0]+=abs(x);//这里用了一个小技巧，用bool的方式返回坐标可以节省if
	}
	if(judge()) printf("second\n");//1表示第二个人
	else printf("first\n");//否则就是第一个
	return 0;
}
~~~
代码里多次用到了bool,不理解的可以枚举大于、小于两种情况，~~或者点赞关注我~~。

---

## 作者：zeekliu (赞：0)

~~弱弱的问一句：为什么这题没有人发题解？~~

这道题真的就是 ```if``` 与 ```else``` 的简单练习题，但情况繁多，坑也不少，一定注意。

**以下是全部情况**


> 1 $ first\_sum > second\_sum $，则输出 ```first```。

> 2 $ first\_sum < second\_sum $，则输出 ```second```。

> 3 $ first\_sum = second\_sum $，则：

>> 3.1 对于 $ i $ ( $ i \leq \min(first.length(),second.length()) $，

>>> 3.1.1 满足 $ first_i > second_i $，则输出 ```first```。

>>> 3.1.2 满足 $ first_i < second_i $，则输出 ```second```。

>> 3.2 无法找到满足以上要求的 $ i $，则直接比较 $ first.length()$ 和 $ second.length() $，

>>> 3.2.1 $ first.length > second.length() $，输出 ```first```。

>>> 3.2.2 $ first.length < second.length() $，输出 ```second```。

>>> 3.3.3 最后是谁得分的。

太复杂了，我快要晕了，看代码吧。

```cpp
//CF493B 22-08-20
#include <bits/stdc++.h>
using namespace std;
int n,a[2000010],b[2000010];
long long x,p=0,q=0,f=0,s=0,ff;

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	a[0]=0;b[0]=0;
	for (int i=1;i<=n;i++)
	{
		cin>>x;
		if (x>0) f++,a[f]=x,p+=x;
		else if (x<0) s++,b[s]=-x,q-=x;
		if (i==n && x>0) ff=1;
		else if (i==n && x<0) ff=2;  
	}
	if (p>q) cout<<"first"<<endl;
	else if (q>p) cout<<"second"<<endl;
	else if (p==q)
	{
		for (int i=1;i<=min(f,s);i++)
		{
			if (a[i]>b[i]) {cout<<"first"<<endl;exit(0);}
			if (b[i]>a[i]) {cout<<"second"<<endl;exit(0);}
		}
		if (f>s) cout<<"first"<<endl;
		else if (s>f) cout<<"second"<<endl;
		else if (ff==1) cout<<"first"<<endl;
		else cout<<"second"<<endl;
	}
	return 0;
}
```

注：以上 ```exit(0)``` 表示退出程序，在主函数里可以理解为与 ```return 0;``` 	有相同的作用。

---

