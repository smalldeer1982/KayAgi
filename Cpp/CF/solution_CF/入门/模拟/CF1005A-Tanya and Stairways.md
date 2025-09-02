# Tanya and Stairways

## 题目描述

给你N个数（1≤N≤1000），这N个数是由M个从1开始的连续自然序列组成的

## 样例 #1

### 输入

```
7
1 2 3 1 2 3 4
```

### 输出

```
2
3 4 ```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
4
1 1 1 1 ```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
5 ```

## 样例 #4

### 输入

```
5
1 2 1 2 1
```

### 输出

```
3
2 2 1 ```

# 题解

## 作者：Register (赞：4)

# 现在只刷的动这种CF模拟水题了。。。
这就是求这串东西有多少个从1开始的连续自然数序列，和这个序列有多长，想必我也不用再解释了。。。

直接上代码吧：
```cpp
#include <iostream>//输入输出流库
using namespace std;
int main(){
	int a[1001],n,sum=0/*用来统计有多少个序列的*/;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		if(a[i]==1) sum++/*有多少个1就代表有多少个序列*/;
	cout<<sum<<endl;//首先输出序列个数
	for(int i=1;i<n;i++)
		if(a[i+1]==1) cout<<a[i]<<" ";//输出每一个序列的长度，也就是每一个1之前的数
	cout<<a[n]<<endl;//最后额外输出最后一项，即最后一个序列的长度
	return 0;
}
```
~~忽然感觉自己的打字速度变快了~~

---

## 作者：LiteratureCollege (赞：1)

这一题的难度其实很低，只是题面有一点难理解，只要理解了题意，此题就很简单了。

**一句话题意：求一个序列中自然数序列的个数以及它长度。**

那么我们只需要从枚举序列开头，慢慢往后找就行了，序列的长度需要存在答案数组中。


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,zjy,gy[1416],a[1416];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;)//因为下面循环已经更改过i了，此处便不需要i++了 
	{
		if(a[i]==1)
		{
			i++;
			zjy++;
			while(a[i]==a[i-1]+1)
			{
				gy[zjy]++;
				i++;
			}
		}
	}
	cout<<zjy<<endl;
	for(int i=1;i<=zjy;i++)
	{
		cout<<gy[i]+1<<" ";//记住这里要加1 
	}
	return 0;
}
```


---

## 作者：piggymichael (赞：1)

就是求有多少个从1开始的连续自然数序列，这个序列有多长。那么一碰到1就是一个新的序列然后统计一下多长就行了。

看代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,judge=0,sum=0,ans[1010],a;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a;//边输入边算
        if(a==1)//如果开始了一个新的序列
        {
            sum++;//统计总共有几个序列
            if(i!=1)
            {
                ans[sum]=judge+1;//记录上一个的长度
                judge=0;//长度归零
            }
        }
        else
            judge++;//长度加1
    }
    cout<<sum<<endl;
    for(int i=2;i<=sum;++i)
        cout<<ans[i]<<" ";
    cout<<judge+1<<endl;
    return 0;
}
```
就这样结束啦！

---

## 作者：daniEl_lElE (赞：0)

## 我又来刷水题了QwQ

#### 此题做法：

1. 输入（不用说）。

2. 用一个数组存下来每一段总和并赋值为0。

3. 每遇到一个1，就新开一个段并将这一段的大小增加一。

4. 如果不是一，就将本段大小增加一。

5. 输出（又是不用说的）。

#### 提示：

1. 输入输出格式。

2. 一定要赋值为0！

3. 注意细节部分。
#### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n,sum=0;
	cin>>n;
	int a[n+1],b[1005]={0};
	for(int i=1;i<=n;i++){
	    b[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1){
			sum++;
			b[sum]++;
		}
		else{
		    b[sum]++;
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++){
		cout<<b[i]<<" ";
	}

	return 0;
}
```

---

## 作者：Vocanda (赞：0)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF1005A)

# 分析
题目的意思就是给你一个序列，让你找到其中有多少以 $1$ 开头的上升的序列。

那么我们就可以在读入的时候就进行判断，因为每个序列的开头必须是 $1$ ，所以我们在读入到 $1$ 的时候就记录一下当前这个的位置，因为要求每个序列的长度，而最后一个序列是没有后边的 $1$ 的，所以我们在结尾加上一个 $1$ ，在输出长度的时候从第二个 $1$ 的位置开始输出，每一次输出当前位置与上一个位置的差，就是长度，最后到结尾。

至于多少个上升的序列，我们只需要求里边有多少个 $1$ 就行了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int L = 1 << 20;
char buffer[L],*S,*T;
#define getchar() (S == T && (T = (S = buffer) + fread(buffer,1,L,stdin),S == T) ? EOF : *S++)
inline int read(){
	int s = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		s = s *10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
const int maxn = 1e5+10;
int jl[maxn];
int cnt;
int main(){
	int n = read();
	for(int i = 1;i <= n;++i){
		int x = read();
		if(x == 1){
			jl[++cnt] = i;//记录位置和个数
		}
	}
	jl[++cnt] = n + 1;//最后加一个 1 的位置
	printf("%d\n",cnt - 1);
	for(int i = 2;i <= cnt;++i){//从第二个 1 开始枚举
		printf("%d ",jl[i] - jl[i-1]);
	}
	return 0;
}

```

---

## 作者：Franka (赞：0)

### **题目**
求数组a中有多少个从1开始的连续自然数序列。
### **思路**
m其实就是只需将a数组中1出现的次数。

接着m个数，输出所在的一的前一个数。

最后输出最后一个数。
### **代码**
```pascal
var
 n,m,i:longint;//定义n、m和i
 a:array[0..1001] of longint;//定义a数组
begin
 readln(n);//读入n
 for i:=1 to n do//边读入边做
  begin
   read(a[i]);//读入a[i]
   if a[i]=1 then inc(m);//如果a[i]等于1，m加1
  end;
 writeln(m);//输出m
 for i:=1 to n-1 do//因为最后一个单独输出，所以不用算进去
  if a[i+1]=1 then write(a[i],' ');//模拟
 writeln(a[n]);//输出最后一个
end.
```


---

## 作者：williamlyz (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1005A)

这么水的题为什么好多大佬都要用栈去做，好了好了，说正经的。

**题意**

给定一个长度为n的数列，问数列中有几个从1开始的连续自然序列，并且给出每个序列的长度。

**思路**

首先统计符合要求子序列的个数，非常简单，只要统计数列中有几个1就可以了，因为每个子序列第一个数必须是1；

接下来是输出每个子序列的长度，由于是从1开始的连续自然序列，每个序列的最后一个数是和每个子序列的长度是一样的，所以输出每个子序列的最后一个数就行啦；那么怎样确定每个子序列的最后一个数呢？我们将数列的每个数依次和他后面那个数比，如果这个数比他后面这个数大或者等于他后面的数，这就是子序列的最后一个数。

**上代码**
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int a[1005];
int main()
{
	int n,sum=0;
	cin>>n;//输入不用我解释了吧 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入不用我解释了吧 
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)//统计数列中有几个1 
			sum++; 
	}
	cout<<sum<<endl;//输出子序列个数 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=a[i+1])//求每个子序列的末尾数 
			cout<<a[i]<<" ";
	}
	return 0;//好习惯 
}


```

接下来我简化简化，挑战最短代码，只有11行（压行过）：
```cpp
#include<bits/stdc++.h>
int a[1005],b[1005];
int main()
{
	int n,sum=0;std::cin>>n;
	for(int i=1;i<=n;i++) std::cin>>a[i];	
	for(int i=1;i<=n;i++) if(a[i]==1) sum++; 
	std::cout<<sum<<std::endl;
	for(int i=1;i<=n;i++) if(a[i]>=a[i+1]) std::cout<<a[i]<<" ";	
	return 0;
}
```





---

## 作者：文·和 (赞：0)

大体思路不难，这里冲一冲花式代码

### 答案无法储存咋办？？
```
queue<int> q;
```
队列有时有奇效

思路：如果不是1则连续记录++，否则记录答案。记住最后还要判断一次。

```
#include <bits/stdc++.h>
using namespace std;
int i,n,j,a,k,ans;//a为输入，k为连续的记录变量，ans为个数
queue<int> q;//答案队列
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		if(a==1&&k>0) ans++,q.push(k),k=1; //如果是1那么记录这个答案
		else k++;//否则连续++
	}
	if(k>0) ans++,q.push(k),k=0;//再做一次处理
	cout<<ans<<endl;
	for(i=1;i<=q.size();i++){
		cout<<q.front()<<" ";
		q.push(q.front());   //遍历队列并输出
		q.pop();
	}
	return 0;
}
```


---

## 作者：Jelly_Goat (赞：0)

结合博客更好食用[本题解](https://www.cnblogs.com/jelly123/p/10394244.html)  
楼上别说这个题水，这个题可能还真有不知道的知识点。  
看到这个题，想到刚学的**单调栈**。

------

### 单调栈？
单调栈和单调队列差不多，但是我们只用到它的栈顶。  
单调，意思就是一直递增或者递减。  

#### 这跟这个题有什么关系？
我们看到这个题说:
>这N个数是由M个从1开始的连续自然序列组成的  

也就是说，我们求的是一些单调栈的大小。  
好说！STL，上！  
**我们开一堆栈，当进去的序列非大于等于原先栈内的栈顶，就压进当前栈；  
否则，换一个栈继续压。**  
然后我们用`.size()`挨个输出栈的大小。  
这里我们可以将栈看作是一个单调的序列——  
是不是挺珂幻？  
上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;
int n,m,trans=1,a[1001];//trans表示当前栈的下标，a[]是原序列
stack<int>qwq[1001];//开栈
int main()
{
    cin>>n;
    for (register int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for (register int i=1;i<=n;i++)
    {
        if (qwq[trans].empty())//空，第一个，压入第一个元素
        {
            qwq[trans].push(a[i]);
        }
        else
        {
            if (qwq[trans].top()>=a[i])//不满足单调递增
            {
                trans++;//换一个栈
            }
            qwq[trans].push(a[i]);//然后压进去
        }
    }
    cout<<trans<<'\n';//最后一个的下标就是栈的数量
    for (register int i=1;i<=trans;i++)
    {
        cout<<qwq[i].size()<<' ';//输出栈大小
    }
    return 0;
}
```

---

## 作者：三牧姚承远 (赞：0)

一道简单的模拟题，如果不是连号，就记录步数
```cpp
#include<iostream>
#define M 1010
using namespace std;
int main()
{
	int n,p,sta[M],top=0,cnt=1;
	cin>>n>>p;
	for(int i=1;i<n;i++)
	{
		int t;
		cin>>t;
		if(t==p+1)
		{
			cnt++;
			p++;
		}
		else
		{
			sta[top++]=cnt;
			p=t;
			cnt=1;
		}
	}
	sta[top++]=cnt;
	cout<<top<<'\n';
	for(int i=0;i<top;i++)
		cout<<sta[i]<<' ';
	return!(cout<<'\n');
}
```

---

## 作者：shaocy (赞：0)

这题其实很水，我只是一个小小的弱小的编程者，请大神们指教。

本题思路：

其实就是判断递增序列，先判a[i]是否等于a[i+1]-1，不相等，则说明这不是一个递增数列，s++。
                                               
相等，说明是递增，继续做下去，直到a[i]!=a[i+1]-1。

其次，提醒一下一些大神，s不要忘记清0这样的小错误而导致无法AC。

下面直接上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n],b[n],j=1;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]+1!=a[i+1]){
			b[j]=a[i];
			j++;
		}
	}
	cout<<j-1<<endl;
	for(int i=1;i<=j-1;i++)cout<<b[i]<<" ";
	return 0;
}

```

---

