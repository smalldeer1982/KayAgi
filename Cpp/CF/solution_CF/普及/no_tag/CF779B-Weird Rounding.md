# Weird Rounding

## 题目描述

Polycarp is crazy about round numbers. He especially likes the numbers divisible by $ 10^{k} $ .

In the given number of $ n $ Polycarp wants to remove the least number of digits to get a number that is divisible by $ 10^{k} $ . For example, if $ k=3 $ , in the number 30020 it is enough to delete a single digit (2). In this case, the result is 3000 that is divisible by $ 10^{3}=1000 $ .

Write a program that prints the minimum number of digits to be deleted from the given integer number $ n $ , so that the result is divisible by $ 10^{k} $ . The result should not start with the unnecessary leading zero (i.e., zero can start only the number 0, which is required to be written as exactly one digit).

It is guaranteed that the answer exists.

## 说明/提示

In the example 2 you can remove two digits: 1 and any 0. The result is number 0 which is divisible by any number.

## 样例 #1

### 输入

```
30020 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
100 9
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10203049 2
```

### 输出

```
3
```

# 题解

## 作者：alex_liu (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF779B)

## 题意：
在数字 $n$ 内删除某些数字，使得可以被 $10^k$ 整除

## 思路：
既然要使 $n$ 能被 $10^k$ 整除，那么 $n$ 的后 $k$ 个数就一定为 $0$ 

那么就可以从 $n$ 的末尾往前推，一共找到 $k$ 个 $0$ 时即可停止

分两种情况：

1. 末尾可以存在 $k$ 个 $0$
2. 末尾不可以存在 $k$ 个 $0$，那么直接删到只剩一个 $0$ 即可

既然要每一位分开处理，那么我们就可以用字符串解决

详细的每一步的解析可以看代码注释

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;//定义字符串 
int k,cnt=0,ans=0;//cnt 为 数字串的 0 的个数；ans 是数字串中非零数的个数，即需要删除的数 
int main(){
	cin>>n>>k;//输入 
	for(int i=n.size()-1;i>=0;i--){//从后往前枚举 
		if(cnt>=k)break;//末尾已经有 k 个 0 ，那么可以退出循环 
		if(n[i]=='0')cnt++;//找到一个 0 
		else ans++;//不是 0 ，那么就是需要删除的数字 
	}
	if(cnt>=k)cout<<ans<<endl;//末尾可以有 k 个 0，则输出要删除的数 
	else cout<<n.size()-1<<endl;//否则就删到只剩一个 0  
	return 0;//完结撒花 
}
```


---

## 作者：Aragron_II (赞：2)

一道字符串的模拟题目，与[P1106](https://www.luogu.com.cn/problem/P1106)有些相似之处。

#### 题意：

求将n删去多少个字符后能被 $ 10 ^ k $ 整除

其中 $ （ 0 ≤ n ≤ 2 * $  $ 10 ^ 9  $ ） 所以 $ n $ 用字符串替代。 

#### 思路：

1. 如果字符串 $ n $ 的零的个数小于 $ k $ ，那么直接输出 $ len(s)-1 $ 
2. 否则从 $ s $ 的后面往前扫,维护答案，没有前导0即可。



$ Code 1 $:


```c
	cin>>n>>k; //输入
    Lens=n.size(); //求字符串长度
    for(int i=0;i<Lens;i++)//循环统计0个数
        if(n[i]=='0') 
            zero++;
    if(zero<k) cout<<Lens-1<<endl; //如果情况1出现则直接输出，如上述1
```



 
$ Code 2 $:
```c
	else { 
        int num=0; 
        for(int i=Lens-1;i>=0;i--) { //从后往前扫
            if(n[i]!='0') num++; //允许删去
            if(n[i]=='0') k--;//0个数
            if(k==0) break; //如果0>=k则退出循环
        }
        cout<<num<<endl;//输出
    }
```


---

## 作者：Proxima_Centauri (赞：1)

[原题目](https://www.luogu.com.cn/problem/CF779B)

好了，话不多说，进入正题。
# 题意
这个题······难度还算可以，很适合我这样的萌新蒟蒻。

我们~~简要分析一下~~扫一眼题目，这个题就是从一个数中，删掉一堆没用的数字，让它变成一个类似```XX···XX00···0```
的数。
# 分析
呃···可能是因为最近一直在~~死磕~~与字符串友好相处，所以我立刻想到了字符串~~因为没加头文件调了好久~~。


然后，倒着从字符串的后面开始枚举，对每一位数字秉着大致这样的思路——

算算从末尾到当前有多少个 $0$；
```
if (s[i] == '0') cnt++;
```


因为有 $k$ 个 $0$ 就满足条件了，所以我们进行如下的判定：
```
if (cnt == k) 
{
	cout << s.size() - i - cnt << endl;
	//枚举到第i时已经有了k个0,（满足条件）
	return 0;
}
```
```s.size() - i```表示当前已经枚举了多少数，在这些数中除掉 $cnt$ 个 $0$ 就是要删去的，算完之后直接 ```return``` 结束程序。

最后，如果算完整个字符串，还没有找到 $k$ 个 $0$，说明这个数没有办法删去若干数字后满足条件，只能使出最后的办法——删成 $0$，共有 ```s.size() - 1``` 个数要被删去：
```
cout << s.size() - 1 << endl;
```
于是，提交评测，AC。
# AC code
最后的最后，放上本蒟蒻丑陋的代码，还请各位大佬见谅：
```
#include <iostream>
#include <string> 
using namespace std;

int main()
{
    string s;
    int k;
    cin >> s >> k;
    int cnt = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
    	if (s[i] == '0') cnt++;
    	if (cnt == k) 
    	{
    		cout << s.size() - i - cnt << endl;
    		return 0;
		}
	}
	cout << s.size() - 1 << endl;
    return 0;
}
```

本蒟蒻的第一篇题解。

---

## 作者：caibet (赞：1)

### 题意：

已知 $n,k$，求把 $n$ 删去几个数字后能被 $10^k$ 整除。

### 解法：

首先，为了使 $n$ 能被 $10$ 的倍数整除，我们肯定要先删除非 $0$ 的数字。而且题目保证数据有解，则 $n$ 肯定含有数字 $0$。

分两种情况看：

- 当要删除的数不含 $n$ 的最高位时：

那很好啊，直接看 $n$ 除了最高位的每个数字，如果有不为 $0$ 的数字，则要删除它。而求一个整数的每个数位是我们所擅长的。当然，如果删掉一个数以后，$n$ 已经可以被 $10^k$ 整除了，那就不需要再删数了。

该情况代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int cur=1;//当然，我们需要一个变量来记录删完数后的 n
int sum;//需要删掉的数的个数
int t=1;
int main(){
	cin>>n>>k;
	while(k--) t*=10;//求 10 的 k 次方
	while(n){
		if(cur%t==0){
			cout<<sum;
			return 0;//不用删了 
		}
		if(n%10==0) cur*=10;//如果当前数位为 0，则删完之后的 n 要多一个 0，即原来的 10 倍。
		else sum++;//多删一个数
		n/=10;
	}
	return 0;
}
```

可是我们仍然是过不了样例 $2$ 的，这时我们就需要考虑另一种情况：

- 当要删除的数含有 $n$ 的最高位时：

也就是说，删掉除了最高位以外的数也不能让 $n$ 被 $10^k$ 整除。既然这样，那我们就只能删得只剩一个 $0$ 了。而这很简单，除了 $n=0$ 时的恶心数据以外，$n$ 的数位的数量减去 $1$ 就是我们要的答案。

该情况代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int digits;
int t=1;
int main(){
	cin>>n>>k;
	if(n==0){
		cout<<0;
		return 0;//特判
	}
	while(n){
		n/=10;
		digits++;//记录数位个数
	}
	cout<<digits-1;
	return 0;
}
```

把两种情况的代码综合起来，就得到了答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,cur=1,sum,t=1,digits;
int main(){
	cin>>n>>k;
	if(n==0){
		cout<<0;
		return 0;//特判 
	}
	while(k--) t*=10;//求 10 的 k 次方
	while(n){
		if(cur%t==0){
			cout<<sum;
			return 0;//不用删了 
		}
		if(n%10==0) cur*=10;//如果当前数位为 0，则删完之后的 n 要多一个 0，即原来的 10 倍。
		else sum++;//多删一个数
		n/=10;
		digits++;//统计数位个数 
	}
	cout<<digits-1;//除了最高位以外的都删完了还无法整除的情况 
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

[用过都说好的题目传送门。](https://www.luogu.com.cn/problem/CF779B)

不讲废话。

## 简略题目：
将一个数通过删除数位的方式变为 $10^{k}$。

## 教学：
已知 $10^k$ 倍数特征为数的后面有 $k$ 个 $0$，找到后面的 $k$ 个 $0$，记录这些 $0$ 之间的数为需要删除的数，则为正确答案。如果没有 $k$ 个 $0$，那么就只能将这个数删除得只剩下 $0$，因为 $0$ 可以被所有数整除。

## 代码：
由于比较简单，所以请自行理解。
```
#include<bits/stdc++.h>
using namespace std;
long long k,t,ans;
string a;
int main(){
    cin>>a>>k;
    for(int i=a.size()-1;i>=0;i--)
		if(a[i]=='0') 
		{
			t++;
			if(t==k) break;
		}
		else ans++;
	if(t>=k) cout<<ans;
	else cout<<a.size()-1;
    return 0;
}
```

---

## 作者：max666dong123 (赞：0)

## 题目大意
将 $n$ 删除一些字符后，末尾有 $k$ 个 $0$。

## 思路
末尾想要有 $k$ 个 $0$，就需要**从后往前**扫描，记录 $0$ 出现的次数，如果不是 $0$，就记录删除的数量。

但是要是 $0$ 不够呢，比如第二组的 ``100 9`` 就需要保留一个数 $0$，其他的全删除，因为 $0$ 整除任意数。

## AC代码
```cpp 
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
string s; 
int k;
int cnt,ans;
signed main(){
	IOS;
	cin>>s;
	cin>>k;
	for(int i=s.size()-1;i>=0;i--){
		if(cnt>=k){
			cout<<ans<<endl;
			return 0;
		}
		if(s[i]=='0'){
			cnt++;
		}
		else{
			ans++;
		}
	}
	cout<<s.size()-1<<endl;
	return 0;
}

```

---

## 作者：许多 (赞：0)

很简单的字符串题，适合新手入门。

观察题意，我们发现：$0$ 能被任何 $10^k$ 整除。
这样的话当 $n$ 中 $0$ 的个数小于 $k$ 时，我们就可以将数全部删掉，只留一个 $0$。

我们从尾向前看，如果不是 $0$ 就删掉，是 $0$ 我们就记录下来，当 $0$ 的个数等于 $k$ 时，就输出当前一共删了多少数。

# 代码
```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
int ans,k,now=0,del=0;//now表示当前0的个数，del表示当前删了多少个数。
string n;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main(){
	cin>>n;k=read();ans=n.size();
	for(int i=ans-1;i>=0;i--){
		if(n[i]=='0')now++;
		else del++;
		if(now==k){
			printf("%d",del);
			return 0;
		}
	}
	printf("%d",ans-1);//上文中0的个数小于k时。
	return 0;
}

```


---

## 作者：Siteyava_145 (赞：0)

[我的4号传送门](https://www.luogu.com.cn/problem/CF779B)

### **思路：**

- 能否被 $10^k$ 整除，要判断末尾 $0$ 的数量。

- 从数的末尾往前判断，如果已发现的 $0$ 数 $\geq k$，那么直接输出这一段里不为 $0$ 的数的数量（拿计数器存）。

- 循环后再判断一次，保险。

- 如果程序都走到这里了，那就是这个数里的所有 $0$ 的数量 $<k$，这时就只能把数字删的只剩下一个 $0$，答案为数字总位数 $-1$。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int N=n,cnt=0,nw=0;
    if(n==0){cout<<0;return 0;}
    while(N){
        if(cnt>=k){cout<<nw;return 0;}
        if(N%10==0){cnt++;}else{nw++;}
        N/=10;
    }
    if(cnt>=k)cout<<nw;
    else cout<<cnt+nw-1;
}
```


---

## 作者：Noby_Glds (赞：0)

这题算是比较简单的黄题。

### 思路：
分两种情况：

如果这串数字中的 $0$ 的数量小于 $k$：只有数字 $0$ 满足题意，很显然直接输出**这个数字的位数减一**就行了。

反之，从这串数字的最后往前扫，扫到一个不为 $0$ 的数字答案加一，如果扫过的 $0$ 的个数等于 $k$，则跳出循环，输出答案。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int sum,ans,now,k;
int main(){
	cin>>a>>k;
	for(int i=0;i<a.size();i++) if(a[i]=='0') sum++;
	if(sum<k){
		cout<<a.size()-1;
		return 0;
	}
	for(int i=a.size()-1;i>=0;i--){
		if(now==k) break;
		if(a[i]!='0') ans++;
		else now++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## CF779B Weird Rounding
[原题链接](https://www.luogu.com.cn/problem/CF779B)

## 分析
一个数能被 $10^{k}$ 整除，即指这个数除以 $10^{k}$ 的值为整数。设这个数为变量 $a$，得到的整数为 $Z$，条件可以表示为 $a\div 10^{k}=Z$，变形得到 $a\times  10^{-k}=Z$。

我们发现，如果 $a$ 的尾部不是至少连续存在 $k$ 个 $0$，是无法被 $10^{k}$ 整除的。只要比较处理后的数字尾部连续存在 $0$ 的个数和 $k$，就能知道是否可以被整除。

## 思路
既然是从尾部开始找 $0$，能够想到后进先出的数据结构——栈。将数字以字符串的形式读入，再从高位到低位依次入栈，这样将数字顺序倒了过来，我们只需要判断当前栈顶数字是否为 $0$，用两个计数器分别记录 $0$ 和非零数字的数量，将对应的计数器累加，再弹出栈顶元素继续判断。

如果当前记录的 $0$ 的数量已经大于等于 $k$，则删去当前记录的非零数字的数量后可以被整除，输出计数器结束程序。如果直到栈被清空程序仍未被结束，说明只能将数字处理为 $0$，需要删去除一个 $0$ 外的所有数字。即删去 原数字位数减一 个字符。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
stack<char>n;
int num,ans;
int main(){
	string q;cin>>q;
	for(int i=0;i<q.length();i++){
		n.push(q[i]); //各数位依次入栈 
	}
	int b=n.size(); //记录数字位数 
	int k;cin>>k;
	while(!n.empty()){ //栈未被清空 
		if(num>=k){ //处理后，被除数大于等于除数尾部0的个数 
			cout<<ans; //能够整除，输出尾部需要删除的非零数字个数 
			return 0;
		} 
		if(n.top()=='0'){
			num++; //数位为0，累加个数 
			n.pop();
		}else{
			ans++; //数位不为0，累加需要删去的个数 
			n.pop();
		}
	}
	//栈空，处理后，被除数小于除数尾部0的个数 
	cout<<b-1; //需要删去除一个0外所有数字 
	return 0;
}
```


---

## 作者：dalao_see_me (赞：0)

如果有一个数 $N$ ，它能被 $10^k$ 整除，那么这个数必须在最后面有至少连续 $k$ 个零。

于是我们就可以诞生一种非常粗暴的办法，直接从后往前扫。看到零就把存储末尾零的个数的变量加一，看到非零的就将答案加一。

最后特判一下是不是要删成零就可以了。

可以用字符串来处理而非直接用数字，个人认为会方便很多。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,_0=0,ans=0;
int main(){
	cin>>s>>k;
	_0=0;
	for(int i=s.size()-1;i>=0;i--){
		if(_0>=k)break;
		if(s[i]=='0')_0++;
		else ans++;
	}
	if(_0>=k)cout<<ans;
	else cout<<s.size()-1;
	return 0;
}
```


---

