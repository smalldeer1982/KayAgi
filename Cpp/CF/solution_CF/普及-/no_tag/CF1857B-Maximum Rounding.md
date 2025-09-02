# Maximum Rounding

## 题目描述

Given a natural number $ x $ . You can perform the following operation:

- choose a positive integer $ k $ and round $ x $ to the $ k $ -th digit

Note that the positions are numbered from right to left, starting from zero. If the number has $ k $ digits, it is considered that the digit at the $ k $ -th position is equal to $ 0 $ .

The rounding is done as follows:

- if the digit at the $ (k-1) $ -th position is greater than or equal to $ 5 $ , then the digit at the $ k $ -th position is increased by $ 1 $ , otherwise the digit at the $ k $ -th position remains unchanged (mathematical rounding is used).
- if before the operations the digit at the $ k $ -th position was $ 9 $ , and it should be increased by $ 1 $ , then we search for the least position $ k' $ ( $ k'>k $ ), where the digit at the $ k' $ -th position is less than $ 9 $ and add $ 1 $ to the digit at the $ k' $ -th position. Then we assign $ k=k' $ .
- after that, all digits which positions are less than $ k $ are replaced with zeros.

Your task is to make $ x $ as large as possible, if you can perform the operation as many times as you want.

For example, if $ x $ is equal to $ 3451 $ , then if you choose consecutively:

- $ k=1 $ , then after the operation $ x $ will become $ 3450 $
- $ k=2 $ , then after the operation $ x $ will become $ 3500 $
- $ k=3 $ , then after the operation $ x $ will become $ 4000 $
- $ k=4 $ , then after the operation $ x $ will become $ 0 $

 To maximize the answer, you need to choose $ k=2 $ first, and then $ k=3 $ , then the number will become $ 4000 $ .

## 说明/提示

In the first sample, it is better not to perform any operations.

In the second sample, you can perform one operation and obtain $ 10 $ .

In the third sample, you can choose $ k=1 $ or $ k=2 $ . In both cases the answer will be $ 100 $ .

## 样例 #1

### 输入

```
10
1
5
99
913
1980
20444
20445
60947
419860
40862016542130810467```

### 输出

```
1
10
100
1000
2000
20444
21000
100000
420000
41000000000000000000```

# 题解

## 作者：Dream_poetry (赞：6)

### 思路：
既然是四舍五入，那当然是越往**左**越应该**入**，这样才能使修改后的数更大。

我们可以把整个字符串自右向左扫，只要满足了进位条件，那就进位。并将标记放到这里。

最后输出时，只要在非标记区域，正常输出即可，否则输出 0。

### 代码：
```cpp

#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		s='0'+s;//预处理最高位
		int sswr=s.size();
		for (int i=s.size()-1;i>0;i--){
			if (s[i]=='9'+1){ //满十进一
				s[i]='0';
				s[i-1]++;
			}
			if (s[i]>='5'){ //五入
				sswr=i;
				s[i-1]++;
			}
		}
		for (int i=0;i<s.size();i++){ //输出
			if (i==0 && s[i]=='0') continue;
			if (i<sswr) cout<<s[i];
			else cout<<'0'; 
		}
		puts("");
	}
	return 0;
} 
```


---

## 作者：LIUYC_C (赞：2)

[题目链接。](https://www.luogu.com.cn/problem/CF1857B)

### 思路：
模拟的时候有些猪脑过载，写得很乱，搞得很难调，后面索性全删了，重写之后思路就很清晰了。

首先观察到两个性质，每个数位最多只会进一位，并且第一个大于等于五的数，包括其本身的，后面的数全都会更新成 0，然后第一个大于等于五的数的前面的数如果是 4 的话，也可以进位，那么这一位也更新成 0 ，递推下去找到第一个不是 4 的数，让它加上一就好了，最后输出字符串，具体看代码实现。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
 
int main(){
    int t;
    cin>>t;
    for(int k=1;k<=t;k++){
       string s;
       cin>>s;
       s='0'+s;
       for(int i=1;i<s.size();i++){
           if(s[i]-'0'>=5){
               int tim=i-1;
               for(int j=i;j<s.size();j++){
                   s[j]='0';
               }
               while(s[tim]-'0'==4){
                   s[tim]='0';
                   tim--;
               }
               
               s[tim]=char(s[tim]+1);
               break;
           }
       }
        
        if(s[0]-'0'!=0){
            cout<<s[0];
        }
        
       for(int i=1;i<s.size();i++){
           cout<<s[i];
       }
       cout<<endl;
       
    }
    
}
```



---

## 作者：Wf_yjqd (赞：1)

题面挺复杂的，实际很简单。

------------

可以理解为一个数的小数部分，可以任意次选择一位四舍五入，最大化最终的数。

显然要找到最高的可以进位的一位。

从高往低枚举每一位，若大于等于 $5$ 或者存在一段连续的 $4$ 且 $4$ 后的一个数大于等于 $5$，这一位就可以进位。

按题意模拟即可，复杂度 $\operatorname{O}(n)$。

------------

可以看看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,len,pos;
char s[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        len=strlen(s+1);
        s[0]='0';
        pos=-168;
        for(int i=1;i<=len;i++){
            if(s[i]>='5'){
                pos=i;
                break;
            }
            if(s[i]=='4'){
                int j;
                for(j=i+1;j<=len;j++)
                    if(s[j]!='4')
                        break;
                if(s[j]>'4'){
                    pos=i;
                    break;
                }
                i=j;
            }
        }
        if(pos<-1){
            puts(s+1);
            continue;
        }
        while(s[pos-1]=='9')
            pos--;
        s[pos-1]++;
        for(int i=min(1,pos-1);i<=len;i++)
            putchar(i<pos?s[i]:'0');
        puts("");
    }
    return 0;
}
```


---

## 作者：Special_Tony (赞：1)

[洛谷传送门](/problem/CF1857B) & [CF 传送门](//codeforces.com/problemset/problem/1857/B)
# 思路
这题可以用贪心做，**倒着**遍历，看这一位上的数字是否 $\ge5$，如果是的，那就直接四舍五入。
# 注意事项
1. 要**倒着**遍历；
1. 每次处理时不能直接把 $1\sim i$ 清零，而应该记录一个 $last$ 标记，在输出的时候处理即可；
1. 处理时注意进位；
1. 注意有时候最高位还能进位，这种情况特殊处理。

# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int t, last;
string a;
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法
		cin >> a;
		last = a.size (); //多组数据要清空
		for (int i = a.size (); -- i;)
			if (a[i] > '9') //判断当前是否需要进位
				a[i] = '0', ++ a[i - 1];
			else if (a[i] > '4') { //判断当前是否可以五入
				last = i; //记录下来
				++ a[i - 1]; //下一位 +1
			}
		if (a[0] > '4') { //最高位是否可以五入或需要进位
			cout << 1;
			for (int i = 0; i < a.size (); ++ i)
				cout << 0;
		} else {
			for (int i = 0; i < last; ++ i)
				cout << a[i]; //前面部分正常输出
			for (int i = last; i < a.size (); ++ i)
				cout << 0; //后面部分全变 0
		}
		cout << '\n'; //别忘了换行
	}
	return 0; //结束程序
}
```

---

## 作者：WsW_ (赞：1)

### 思路
如果一个数字在其第 $k$ 位进行了一次四舍五入，那么这个数字的第 $1\sim k$ 位都会变成 $0$。  
要求进行多次操作后数字尽可能大，那我们尽量让数字“五入”得多，而且不进行“四舍”。  
也就是说，当某位上的数字大于 $5$ 的时候，我们在这一位进行一次四舍五入；其他情况不进行操作。  
另外，我们要让最后一次“五入”尽可能在高位，这样就能保证最后数字尽可能大。

我们从最低位开始，能五入就五入，记录五入的最高位。  
输出时五入的最高位后面的数位均为 $0$。

---
### 代码和[提交记录](https://www.luogu.com.cn/record/119644475)
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int w;
string s;
int main(){
	scanf("%d",&t);
	while(t--){
		cin>>s;
		int len=s.length();
		w=len;
		for(int i=len;i>=0;i--){//从最低位开始
			if(s[i]>='5'){//能五入就五入
				w=i-1;
				s[i-1]++;//高位记得+1
				s[i]='0';
			}
		}
		if(w==-1)putchar('1');//特判在最高位五入的情况
		for(int i=0;i<len;i++){
			if(i>w)putchar('0');//第1~k位都被舍去了，0
			else putchar(s[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：tbdsh (赞：1)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1857b)

[洛谷题目传送门](/problem/cf1857b)

[CF 原题传送门](http://codeforces.com/problemset/problem/1857/B)

有 $t$ 组数据。每组数据给定数字 $x(1\le x\le 10^{3500})$ 。

你可以进行任意（可以不进行）次操作，每次操作选择一个位进行四舍五入，最后使得 $x$ 尽可能大。输出这个 $x$。

例如 $x = 3451$ 时选择第二位进行四舍五入会 $x$ 会变成 $3500$。
# 分析
简单的贪心。

首先，因为 $x$ 非常大，我们考虑使用字符串。

显然，进位从低位开始进更好。因为这可能可以让原本无法进位的高位现在可以进位。

如果一位可以进位，那么进位是更划算的。

那么我们就可以把整个数扫一遍。如果一位的值 $\ge 5$，就进位。此时，这一位及其后面的数都要归零。

时间复杂度：$O(\sum |x|)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int t, n, m, a[MAXN];
void Solve(){
  string n;
  cin >> n;
  int len = n.size();
  n = '0' + n;//避免最高位进位数组越界的情况。
  bool vis[MAXN] = {0};
  for (int i = len; i >= 1; i--){
    if (n[i] >= '5'){
      n[i - 1]++, n[i] = '0';
      vis[i] = 1;//如果进位，则进行标记。当前为及以后位都要归零。
    }
  }
  if (n[0] == '0'){//最高位没有进位。
    bool flag = 0;
    for (int i = 1; i <= len; i++){
      cout << (flag ? '0' : n[i]);
      flag |= vis[i];
    }
  }else {//最高位进位。
    bool flag = 0;
    for (int i = 0; i <= len; i++){
      cout << (flag ? '0' : n[i]);
      flag |= vis[i];
    }
  }
  cout << '\n';
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Wiueh_Plus (赞：1)

## 题目大意
给定 $T$ 组数据，每组数据一个自然数 $n$，可以多次选择第 $k$ 位数进行四舍五入，求出四舍五入后该数的最大值。
## 分析思路
思想：**贪心**。

这里给定了两种操作。四舍和五入。显然我们想要让最终的结果最大，我们的操作只能进行**五入**而**不可以进行四舍**。因为如果我们进行了四舍，第 $k$ 位如果小于等于 $4$，那么这一位将要变成 $0$，相对于原数反而变小了，这显然不是我们想要的结果。
## 代码实现
为了方便进位的操作，我们用字符数组来存储输入的数字，再将数组反转过来转换到整型数组。然后对数组进行一次遍历，若当前数位上的数大于或等于 $5$，就将下一位的数 $+1$，表示进了一位。我们再用一个变量 $maxx$ 记录当前可以进位的最高位，$maxx$ 初始为 $-1$。

我们经过观察可以发现：若一个数有进位，那么最高进位的那一位上所有前面的位数都是不变的，后面的位数都是等于 $0$ 的。例如：$419860$，最高进位数为 $k=4$ 那么第五位 $4$ 不变，最高进位的数 $+1$ 等于 $2$，后面的数全部为 $0$，所以最终的结果为 $420000$，那么我们的代码也可以模拟这种方式进行书写。

我们这里分四种情况讨论。

$\bullet$ 当这个数一位都没有进位时（即遍历完后 $maxx$ 仍然等于 $-1$），直接输出原数。

$\bullet$ 当这个数的进位在最高位上且最高位之前是 $9$，现在又进了一位时。

$\bullet$ 当这个数的进位在最高位上且最高位没有再进位时。
（理论上来说第二种和第三种差别不大，都是输出最高位然后后面补 $0$，但代码上稍微有点出入，请看下面的代码。）

$\bullet$ 当这个数的进位在中间的位数时。进位的位数前面的所有数按原数输出，后面的所有数补 $0$ 即可。
### 核心代码：
```cpp
cin >> s;
int len = s.length();
for (int i = 0;i <= len - 1;i++){ //将字符串翻转过来存入整型数组 。 
	arr[i] = s[len - i - 1] - '0';
}
int maxx = -1;
for (int i = 0;i <= len - 1;i++){ //遍历数组，寻找可以五入的位数。 
	if (arr[i] >= 5){
		arr[i + 1]++; //如果当前位数大于等于5，那么五入，即下一位 +1。 
		maxx = i + 1; //更新最高进位的位数。 
	} 
}
if (maxx == -1){ //第一种情况。 
	for (int i = 0;i <= len - 1;i++){
		printf("%lld",arr[len - i - 1]);
	} 
	printf("\n");
}
else if (maxx == len){ //第二种情况。 
	printf("%lld",arr[maxx]);
	for (int i = 0;i <= len - 1;i++){
		printf("0");
	}
	printf("\n");
}
else if (maxx == len - 1){ //第三种情况。 
	printf("%lld",arr[maxx]);
	for (int i = 0;i <= len - 2;i++){
		printf("0");
	}
	printf("\n");
}
else { //第四种情况。 
	for (int i = 0;i <= len - maxx - 2;i++){
		printf("%lld",arr[len - i - 1]);
	}
	printf("%lld",arr[maxx]);
	for (int i = 0;i <= len - (len - maxx - 2) - 3;i++){
		printf("0");
	}
	printf("\n");
}
```



---

## 作者：LEle0309 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1857B) or [CF传送门](https://codeforces.com/problemset/problem/1857/B)

#### 题目大意：

给你一个长度为 $ n $ 的数字 $ x $，选一个 $ k $ 四舍五入到 $ k+1 $ 位，进行若干次这样的操作后，求改变后 $ n $ 的最大值（可以不操作）。

#### 题目分析

$ n \le 2 \times 10^5 $，`long long` 都被~~炸成灰了~~，得用字符串模拟。

首先，特判 $ n=1 $，一位数，大于等于 $ 5 $ 则输出 $ 10 $，否则输出 $ x $。

然后，倒序遍历字符串，如果有大于 $ 5 $ 的，标记处理过（因为如果每一位都小于 $ 5 $，输出原数而不是 $ 0 $），并且更新位数且下一位加 $ 1 $。因为你要 $ n $ 最大，一定要四舍五入到越高的数位越好。

然后，判断首位，大于 $ 5 $ 时输出 $ 1 $ 后面 $ n $ 个 $ 0 $，即四舍五入最高位。
```cpp
#include<iostream>
using namespace std;
int a,t,i,vis,f;string x;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>x;f=0;
		if(x.length()==1&&x[0]>='5')
		{
			cout<<10<<'\n';
			continue;
		}//特判5<=x<10
		else if(x.length()==1&&x[0]<'5')
		{
			cout<<x<<'\n';
			continue; 
		}//特判0<=x<5
		for(i=x.length()-1;i>0;i--)
			if(x[i]>='5')//倒序遍历
			{
				vis=i;//最高位
				x[i-1]++;//下一位加1
				f=1;
			}
		if(x[0]>='5')//特判首位大于5
		{
			cout<<10;
			for(i=1;i<x.length();i++)cout<<0;
			cout<<'\n';
			continue;
		}
		else if(!f)//特判没有四舍五入过
		{
			cout<<x<<'\n';
			continue;
		}
		cout<<x[0];
		for(i=1;i<vis;i++)cout<<x[i];
		for(i=vis;i<x.length();i++)cout<<0;//输出改后数
		x="";cout<<'\n';//注意换行
	}
	return 0;//完结撒花！！！
}
```
#### 总结：

模拟题一定要考虑周全，多特判几个没事，~~别到时候被 hack 了追悔莫及。~~

---

## 作者：_5t0_0r2_ (赞：0)

# 分析:

要想将 $k$ 四舍五入的值最大，说明我们只能“五入”，不能“四舍”。

然后我们还得考虑顺序问题。

例如：$45$ 的最高位一开始不能“五入”，但最后一位“五入后”，第一位也可以“五入”。用通俗的话讲，就是高位的数只能因低位的数“五入”而变大，所以我们应该从低位到高位进行五入操作（即从第 $1$ 到 $\operatorname{len}(x)$ 位）。

---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定一个自然数 $x$，你可以对这个数的各个数位进行如下操作（可以不操作或操作多次）：

- 将其四舍五入至这一位，即，如果这个数位的更低一位大于等于 $5$，那么这个数位加上 $1$（逢十则进一），并将这个数位的所有更低的数位变成 $0$。

问操作后的 $x$ 的最大值可能是多少。本题有多测，共 $t$ 组数据。

$1\le t \le 10^4, 0\le x < 10^{2\times 10^5}$。

### 题目分析

根据题意我们可以发现：如果我们从最右边的数位开始，一旦数位大于 $5$（即可以进一）那么就立刻将其四舍五入，这样就可以让更高的数位进一。例如 $45$，我们把最低位 $5$ 四舍五入变成 $50$，再把 $50$ 的十位 $5$ 进行四舍五入，这样就可以得到最大答案 $100$。

由于 $x$ 非常大，只能用字符串存储，所以我们在求答案时可以将字符串从后往前遍历，一旦可以进位就进位，把之后的所有数字都变成 $0$，这样修改后的字符串就是最佳答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, l, lst;
string s;
int main(){
	scanf("%d", &t);
	while(t--){
		cin >> s;
		l = s.size();
		lst = l; // 存储从哪一位开始就全部变成 0（如果每一次进位时都暴力修改，会 TLE）
		for(int i = l - 1;i >= 0;i--){
			if(s[i] >= '5'){ // 一旦可以进位就进位
				if(i == 0){ // 最高位进位，那么答案就是 10...0，为防止越界先输出 1
					printf("1");
				}
				else{
					s[i - 1]++; // 更高位加上 1
				}
				lst = i; // 其后的数字都变成 0
			}
		}
		for(int i = 0;i < lst;i++){
			printf("%c", s[i]);
		}
		for(int i = lst;i < l;i++){
			printf("0");
		}
		printf("\n");
	}
	return 0;
}


```

---

## 作者：I_am_kunzi (赞：0)

# CF1857B 题解

### 题目翻译

给定一个长度最大为 $ 2 \times 10 ^ 5 $ 的大整数 $ n $，最大化将其若干位都四舍五入后的值。

### 题目思路

其实这道题很容易被题面解释误导，认为需要很复杂的判断，其实不然，例如一个数 $ 20445$，最优解是从最后一位向前舍入得到 $ 21000$；题面中的 $ 3451 $ 从最后一位开始向前舍入也可得到最优解 $ 4000$，所以最优解一定是从最后一位向前舍入。

证明：高位的舍入会将剩下的低位清零，所以最大化结果一定是从最后一位开始舍入，可以尽量减少清零带来的损失；不过如果某一位不足 $ 5 $ 则不能进行舍入，否则清零后结果一定不优。

### 题目代码

```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int a[200005];
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		string s; // 字符串方便读入
		cin >> s;
		memset(a , 0 , sizeof(a));
		int l = s.length();
		for(int i = l - 1 ; i >= 0 ; i--) // 倒序存储方便后续进位操作
		{
			a[l - i] = s[i] - '0';
		}
		int maxup = -1; // maxup 为最大的进位点，因为这一位及后面的都要清零
		for(int i = 1 ; i <= l ; i++)
		{
			if(a[i] >= 5) // 满足进位条件，则进位后结果一定不劣
			{
				maxup = i; // 更新最后一次进位点
				a[i] = 0; // 清零当前位
				a[i + 1]++; // 增加下一位的值
			}
		}
		if(a[l + 1]) // 如果最高位进位，则第 l + 1 位不为 0，需要输出，这是倒序存储的原因
		{
			cout << a[l + 1];
		}
		for(int i = l ; i >= 1 ; i--)
		{
			if(i < maxup) // 因为第 maxup 位已经清零，所以第 maxup 位可以不判
			{
				cout << 0;
			}
			else
			{
				cout << a[i];
			}
		}
		cout << endl; // 这里有人被卡，但是实测这份代码不会 TLE
	}
    return 0;
}

```


---

## 作者：Crazyouth (赞：0)

**翻译**

你可以将一个 $n$ 位的数进行以下操作若干次：

- 选择它的第 $k$ 位，将其四舍五入到第 $k+1$ 位，即如果原来第 $k$ 位大于等于 $5$，将第 $k+1$ 位加一，假如满十则进一，下一步把第 $1$ 位到第 $k$ 位的数变成 $0$。

问这个数最大能变成多少（数的位数编号**从右到左**依次为 $1,2,3,\dots,n$）。

**分析**

记 $x$ 在第 $k$ 位四舍五入后的结果为 $f_k(x)$，记 $len_x$ 为 $x$ 的位数。首先易发现，若 $x$ 的第 $k$ 位小于 $5$，$f_k(x)\le x$，否则 $f_k(x)>x$，所以当 $x$ 的第 $k$ 位小于 $5$ 时，进行操作没有意义。接下来，发现对于 $x>y$，$f_k(x)\ge f_k(y)$，所以从右往左扫一遍每一个位，大于等于 $5$ 就四舍五入一次，并记录位置，然后最后输出的时候大于等于那个位置的就输出 $0$，否则输出原数即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int t,r;
	cin>>t;
	while(t--)
	{
		cin>>s;
		s='0'+s;//空一位，避免最后一位可以四舍五入但是访问到下标-1
		r=s.size();//四舍五入的位置，初值为原数长+1
		for(int i=s.size()-1;i>0;i--)//从低位往高位扫
		{
			if(s[i]=='9'+1)//假如这个数满十，向前进一
			{
				s[i]='0';
				s[i-1]++;
			}
			if(s[i]>='5')//大于等于五就四舍五入
			{
				r=i;//位置移到这
				s[i-1]++;//后一位+1
			}
		}
		for(int i=0;i<s.size();i++)
		{
			if(i==0&&s[i]=='0') continue;//最高位是0，忽略
			if(i<r) cout<<s[i];//没到四舍五入的位置
			else cout<<0;
		}
		cout<<endl;
	}
	return 0;
}

---

## 作者：Failure_Terminator (赞：0)

## Problem

给定一个大整数 $n$，寻找一个数 $k$，使得在第 $k$ 位四舍五入的值最大化，输出最大化的数。

## Solution

显然的，$k$ 一定是 $n$ 内满足 $n_k \ge 5$ 的最高位。

如果没有，应输出原数。

注意：

- 字符串的翻转。

### Note

```cpp
for (int i = 0; i < n; i ++){
	if (i <= t){
		if (s[i] >= '5') s[i + 1] ++; 
		s[i] = '0';
	}
	else{
		if (s[i] >= '5') s[i + 1] ++, s[i] = '0';
	}
}
```

$k$ 位之前无论如何都应舍去，$k$ 位之后只有需进位的要变为 $0$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

void solve(){
	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	int n = s.size();
	int t = -1;
	for (int i = 0; i < n; i ++)
		if (s[i] >= '5') t = i;
	if (t == -1){
		reverse(s.begin(), s.end());
		cout << s << "\n";
	} 
	else{
		s += '0';
		for (int i = 0; i < n; i ++){
			if (i <= t){
				if (s[i] >= '5') s[i + 1] ++; 
				s[i] = '0';
			}
			else{
				if (s[i] >= '5') s[i + 1] ++, s[i] = '0';
			}
		}
		reverse(s.begin(), s.end());
		for (int i = 0; i < s.size(); i ++)
			if (i == 0 && s[i] == '0') continue;
			else cout << s[i];
		puts("");
	}
}

signed main()
{
	int t = read();
	while (t --) solve();
	return 0;
}
```

---

## 作者：LHLeisus (赞：0)

## 题目大意
给定一个自然数 $n$，可以对任意一位进行四舍五入，可以进行任意次，求能得到的最大数。

$n$ 的长度不超过 $2\times 10^5$，没有前导零。

## solution
首先，选择四舍五入的数一定 $\ge 5$，不然对答案没有贡献。

其次，高位的数可能会受到低位的进位，这启发我们从低位向高位考虑。

由于 $n$ 很大，所以选择用数组存储。从低位向高位扫一遍，如果当前数加上进位 $\ge 5$，那么就对这一位打上标记，并让进位加一。最后如果有进位，先将进位输出，接着从高位扫向低位，若此位有标记，那么从当前位向后应该全输出 $0$，否则输出原数接受进位后的结果。
 
 
## code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int INF=0x3f3f3f3f;
int n,m,k;
int A[N];
char s[N];
bitset<N>vis;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		vis.reset();//赋值为0
		scanf("%s",s+1);
		n=strlen(s+1);
		int x=0;
		ROF(i,n,1){
			int t=s[i]-48+x;
			A[i]=t%10;
			x=t/10;
			t=A[i];
			if(t>=5){
				x++;
				vis[i]=1;
			}
		}
		if(x>0) printf("%d",x);
		int f=0;
		FOR(i,1,n) 
		{
			if(vis[i]||f){
				f=1;
				printf("0");
			}
			else printf("%d",A[i]);
		}
		puts("");
	}
	return 0;
}

```


---

