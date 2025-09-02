# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes
```

### 输出

```
2
80
5
composite
```

## 样例 #2

### 输入

```
no
yes
no
no
no
```

### 输出

```
58
59
78
78
2
prime
```

# 题解

## 作者：PC_DOS (赞：7)

既然只能询问20次，我们应该询问哪些东西呢？

首先，我们需要询问所有50以内的质数，它们是:

>2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47

如果一个数可以被分解为两个及以上的质数，那么它必定是合数。

但是如果只这询问这些素数是会WA的，反例就是:

>4, 9, 25, 49

它们都是某个质数的平方，分解质因数时无法分为两个不同的质数，我们需要将它们添加到询问列表里。

于是可以得到代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sAns; //存放给出的应答
	int i,nCount=0; //i-循环计数器，nCount-存放"yes"应答的个数
	int arrAsk[19] = { 2, 3, 4, 5, 9, 7, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49 }; //存放询问的数字
	for (i = 0; i <= 18; ++i){ //一个个询问
		cout << arrAsk[i]<<endl; //提出询问
		fflush(stdout); //刷新流
		cin >> sAns; //读入应答
		if (sAns[0] == 'y'){ //如果应答为"yes"
			++nCount; //计数器加一
		}
		if (nCount >= 2){ //如果有2个及以上的"yes"
			cout << "composite"; //合数
			goto endapp; //结束
		}
	}
	cout << "prime"; //否则为素数
	return 0; //结束
}
```

---

## 作者：lukelin (赞：7)

我们发现判断一个小于100的质数，只用用小于50的质数筛即可  
但是，注意例如4这样的数需要特殊处理  
于是如果输出一个质数的到yes，那么需要判断质数的平方  
**注意**质数的平方如果大于100就别判了

放代码

```cpp
#include <cstdio>
#include <string> 
#include <iostream>

using namespace std;

const int p_num = 15;
int prime[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int main(){
    int cnt = 0;
    string s;
    for (int i = 0; i < p_num; ++i){
        cout << prime[i] << endl;
        fflush(stdout);
        cin >> s;
        if (s[0] == 'y'){
            if ((prime[i] * prime[i]) <= 100){
                cout << (prime[i] * prime[i]) << endl;
                fflush(stdout);
                cin >> s;
                if (s[0] == 'y'){
                    cout << "composite" << endl;
                    return 0;
                }
            }
            ++cnt;
            if (cnt >= 2){
                cout << "composite" << endl;
                return 0;
            }
        }
    }
    if (cnt == 1 || cnt == 0)
        cout << "prime" << endl;
    else
        cout << "composite" << endl;
    fflush(stdout);
    return 0;
}
```

---

## 作者：stdout (赞：3)

~~发题解的人好少啊，那我来发一篇吧~~   
这道题有不少陷阱，~~作为蒟蒻的我被坑了许多(>=2)回QWQ~~   
首先要判断隐藏数(闭合区间$[2,100]$)，我们可以问20个问题。   
而**100以内的合数肯定会被50以内的多(>=2)个素数整除**，例如98可以被2和7整除（本文讨论的整除不包括被1和数的本身整除）。所以马上我们就可以整理出我们的“问题列表”
> 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 (共15个)

~~然后我们就这样写出代码，提交，最后…… WA!~~，为什么呢？   
因为上面的问题对于**平方数**不适用，例如49只能被7整除，所以我们要再增加**针对平方数的问题**。
> 4,9,25,49

注意：**不增加36**，36虽然是平方数，但是它能被2,3,6整除，不需要针对提问。   
现在我们有了一个大概的思路：输出问题，接收回答，当"yes"数大于或等于2时，输出"composite"（合数），否则输出"prime"。   
下面上代码，供参考：（译者提供了模板）
```cpp
#include <iostream>
using namespace std;
const int q[19]={2,3,4,5,7,9,11,13,17,19,23,25,29,31,37,41,43,47,49}; //问题列表
int main()
{
	char ans[4];  //答案
	int cnt=0;  //计数
	for(register int i=0;i<19;i++)  //逐个提问
	{
		cout<<q[i]<<endl;  //提问
		fflush(stdout);  //刷新流
		cin>>ans;  //接收回答
		if(ans[0]=='y') cnt++;  //统计
		if(cnt>=2)  //"yes"数>=2,为合数
		{
			cout<<"composite"<<endl;  //输出判断
			fflush(stdout);
			return 0;  //直接退出
		} 
	}
	cout<<"prime"<<endl;  //输出判断
	fflush(stdout);
	return 0;
}
```
~~求通过……~~

---

## 作者：rsdbk_husky (赞：2)

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

## 一. 审题：

#### 1. 前提条件：

- 无

#### 2. 询问 & 输入：

- 询问：（最多 $20$ 次）

	输出一个数 $x$，代表询问 $x$ 是否是被猜数的约数。
	
- 输入：

	读入一个字符 ```yes``` 或 ```no``` 代表这个数是否是被猜数的约数。

#### 3. 输出：

- 该数是否是素数。

## 二. 思路

- 我们知道质数的因数有且只有 $1$ 和自己，也就是 $1$ 和一个质数。所以第一感觉是把 $1-100$ 的质数问一遍。但很快发现询问次数不够。而且也用不着，因为，**如果只问 1-50 内的质数：**

    1. 如果有2个及以上的 $yes$ 回答，直接判断为合数。

    2. 如果有一个 $yes$ 回答，$51-100$ 不可能有因数，那样所猜数就超100了。

    3. 如果无 $yes$ 回答，$51-100$ 必有且只有一个因数，就是他本身呀。

    所以问 $51-100$ 的质数是无意义的。

- 问完质数还不够，例如 **4** 就判断不出来，因为本交互程序只判断有没有这个因数，不能说出该因数个数。所以还得判断质数的平方数（$100$ 以内的）

## 三. 代码

因为每个输出后都跟了```endl```，所以不需要加```fflush(stdout)```。

```cpp
#include<bits/stdc++.h>

using namespace std;

int primes[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
				  37, 41, 43, 47};	//1-50内质数，共15个
int sq_nums[10] = {4, 9, 25, 49};	//质数的平方数(100以内的) 
string feedback;	//交互返回的字符串
bool once;	//是否已经返回过一次yes了

int main() {
	for (int i = 0; i < 15; ++i) {
		cout << primes[i] << endl;
		cin >> feedback;
		if (feedback == "yes") {
			if (!once) {
				once = 1;
			} else {
				cout << "composite" << endl;
				return 0;
			}
		} 
	}
	for (int i = 0; i < 4; ++i) {
		cout << sq_nums[i] << endl;
		cin >> feedback;
		if (feedback == "yes") {//这些平方数本来就是合数，所以只要返回1次yes就可以判断了
			cout << "composite" << endl;
			return 0;			
		}
	}
	cout << "prime" << endl;
	return 0;
} 
```

---

## 作者：N_z_ (赞：1)

## 题意
* 交互题。
* 交互库生成一个$[2,100]$的数。
* $20$次询问判断是否是质数。
## 题目分析
* $[2,100]$间的所有合数都可以用$2,3,5,7,11,13,17,19,23,29,31,37,41,43,47$组合而成。
* 一个数可以有多个相同数构成，如合数$4=2*2$。

显然，只需输入如上的质数，如果有$2$个及以上返回'yes'即为合数。

如果有一个质数是它的因数，考虑那个质数的平方是否是它的因数。

因此，最多需要询问$16$次。

## 代码
```cpp
#include<bits/stdc++.h>
const int a[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
using namespace std;
int main()
{
    char s[10],cnt=0;
    for(int x=0;x<=14;x++)
    {
        cout<<a[x]<<endl;
        fflush(stdout);
        cin>>s;
        if(s[0]=='y')
        {
            cnt++;
            if(cnt>=2) return puts("composite")*0;
            if(a[x]*a[x]<=100)
            {
                cout<<a[x]*a[x]<<endl;
                fflush(stdout);
                cin>>s;
                if(s[0]=='y')
                {
                    cnt++;
                    if(cnt>=2) return puts("composite")*0;
                }
            }
        }
    }
    cout<<"prime"<<endl;
    fflush(stdout);
    return 0;
}
```
```pascal
const
  a:array[1..15] of integer=(2,3,5,7,11,13,17,19,23,29,31,37,41,43,47);
var
  x,c:integer;
  s:string;
begin
  c:=0;
  for x:=1 to 15 do
  begin
    writeln(a[x]);
    flush(output);
    readln(s);
    if(s[1]='y')then
    begin
      c:=c+1;
      if(c>=2)then begin writeln('composite');exit;end;
      if(a[x]*a[x]<=100)then
      begin
        writeln(a[x]*a[x]);
        flush(output);
        readln(s);
        if(s[1]='y')then
        begin
          c:=c+1;
          if(c>=2)then begin writeln('composite');exit;end;
        end;
      end;
    end;
  end;
  writeln('prime');
  flush(output);
end.
```


---

## 作者：ChthollyForever (赞：1)

## CF679A Bear and Prime 100 题解

这是一道 **交互题**

有一个在闭区间$[2,100]$里面的整数X，你的任务是判断整数x是质数还是合数，我们可以问20次。

容易知道：**100以内的合数肯定会被50以内的多(>=2)个素数整除**
（及“1+1”定理，虽然没有证明，但在100以内足够了）

eg：15 = 3 * 5，77 = 7 * 11 ......


由于在$[2,50]$只有

[${2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}$ ] 

这 15 个素数，所以我~~天真的以为出题人脑子进水了，多给了5次询问~~，交了上去，理所当然的 **WA** 了。

为什么呢？


因为上面的询问对于平方数不适用，例如49只能被7整除，所以我们要再增加针对平方数的询问。见下

$2^2$ = 4; $3^2$ = 9; $5^2$ = 25; $7^2$ = 49; 

(同“1+1”定理，只在 50 以内找）


```cpp

#include <iostream>

const int q[19]={2,3,4,5,7,9,11,13,17,19,23,
25,29,31,37,41,43,47,49}; // 打表

void CF679A() {
    char ans[4];
    cnt=0;
    for(int i=0;i<19;i++) {
        std::cout<<q[i]<<std::endl; // 询问
        fflush(stdout); // 清空输出
        std::cin>>ans;
        if(ans[0]=='y') cnt++;
        if(cnt>=2) {
            std::cout<<"composte"<<std::endl; // 判断
            fflush(stdout);
            return; // 成功后，直接返回
        } 
    }
    std::cout<<"prime"<<std::endl; // 同上
    fflush(stdout);
    return;
}

int main() {
    CF679A();
    return 0; // 完结
}

```

~~第一次发题解，求过~~


---

## 作者：cyrxdzj (赞：0)

### 一、思路

可以证明，从下面的质数中选择 $2$ 次（每次选择的质数可以相同），然后相乘，就可以组成所有大于等于 $2$ 并小于等于 $100$ 的合数。

$$2,3,5,7,11,13,17,19,23,29,31,37,41,43,47$$

因此，我们可以询问这些数是不是 $x$（意义如题目）的因数。如果其中有 $2$ 个或以上的数是 $x$ 的因数，$x$ 就是合数。否则就是质数。

但是，举几个反例：$4$、$9$、$25$、$49$。

这些数都是一个质数的平方。

因此，我们还需要考虑询问的数的平方是不是 $x$ 的因数。

由此，我们得出了完整代码。

### 二、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int ask[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};//存储需要询问的数。
int cnt;//因数个数。
int main()
{
	for(int i=0;i<15;i++)
	{
		printf("%d\n",ask[i]);//询问。
		fflush(stdout);
		char status[4];
		scanf("%s",&status);
		if(status[0]=='y')//询问的数是x的因数。
		{
			cnt++;
			if(ask[i]*ask[i]<=100)//询问的数的平方有可能是x的因数。
			{
				printf("%d\n",ask[i]*ask[i]);//再询问一次。
				fflush(stdout);
				scanf("%s",&status);
				if(status[0]=='y')
				{
					cnt++;
				}
			}
		}
		if(cnt>=2)//因数个数大于2。
		{
			printf("composite\n");
			return 0;
		}
	}
	printf("prime\n");
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/51843130>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：a1ioua (赞：0)

这是一道比较水的交互题。

首先我们可以知道：在 $100$ 里面的合数，一定是 $2$ 或以上在 $50$ 以内的质数合成的。（比如说： $94=2*47,99=3*3*11$ 等。）

但是上面的性质不满足这些平方数：$2^2=4,3^2=9,5^2=25,7^2=49$。所以说：我们可以询问 $19$ 次。

核心代码：
```cpp
inline int solve() {
	for (int i = 1; i <= 19; i++) {
		printf("%d\n", zs[i]);
		fflush(stdout);
		string s;
		cin >> s;
		if (s[0] == 'y') cnt++;
		if (cnt >= 2) {
			printf("composite\n");
			fflush(stdout);
			return 0;
		}
	}
	printf("prime\n");
	fflush(stdout);
    return 0;
}
```

---

## 作者：happybob (赞：0)

~~其实我根本不知道交互提中的flush是啥，所以我根本没用fflush(stdout)~~

如果一个数可以分解为两个及以上的质因数，那就是合数。

证明：

对于任意一个合数X，小学理论已经证明出X可以被某个质数整除，将X除以这个质数，得数如果是质数，那么X有两个质因数，否则，将X除以这个质数的结果继续分解，最后会有 >= 2个质因数

但对于 $\large p$ 为质数，将C设为形如 $\Large p ^ n$的数，将C分解质因数，可得出：

$\LARGE C = p ^ n$

因此，C只有一个质因数

所以对于平方数是个问题，例如9，3 * 3 = 9所以9为合数，但3只是一个质因数，所以要加3， 5， 9到表中

我不会fflush，哇：

```cpp
#include <iostream>
using namespace std;

char ch[5];

const int zs[20] = {0, 2, 3, 4, 5, 7, 9, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};

int main()
{
    int cnt = 0;
    for(register int i = 1; i <= 19; i++)
    {
        cout << zs[i] << endl;
        cin >> ch;
        if(ch[0] == 'y')
        {
            cnt++;
        }
        if(cnt >= 2)
        {
            cout << "composite\n";
            return 0;
        }
    }
    cout << "prime\n";
    return 0;
}
```


---

