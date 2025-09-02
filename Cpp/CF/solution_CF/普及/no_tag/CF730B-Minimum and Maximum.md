# Minimum and Maximum

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

In this problem, you need to find maximal and minimal elements of an array. What could be simpler?

You can imagine that the jury has an array, and initially you know the only number $ n $ — array's length.

Array's elements are numbered from $ 1 $ to $ n $ . You are allowed to compare two elements of the array by using their indices $ i $ and $ j $ . There are three possible responses to this query: '<' (if $ a_{i} $ is less than $ a_{j} $ ), '=' (if $ a_{i} $ is equal to $ a_{j} $ ) and finally '>' (if $ a_{i} $ is greater than $ a_{j} $ ).

It's known that it's always possible to find both maximal and minimal elements of the array by using no more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF730B/64e27b3d6ef68e5168a71a1fda863cd37a7518ef.png) comparisons, where $ ⌈\ x⌉ $ is the result of rounding $ x $ up.

Write the program that will find positions of the minimum and the maximum in the jury's array of length $ n $ , by using no more than $ f(n) $ comparisons.

## 样例 #1

### 输入

```
2
2
 
&gt;
 
3
 
=
 
=
 ```

### 输出

```
 
 
? 1 2
 
! 2 1
 
? 3 1
 
? 2 1
 
! 2 3```

# 题解

## 作者：skyskyCCC (赞：0)

## 前言。
交互题，采用递推的思路。
## 分析。
有一个很显然的思路就是我们我们可以通过进行两两比较分出两个数组，一个存在某次询问中的较大值的编号，另一个存较小值的编号，那么我们就可以在 $\frac{n}{2}$ 的次数内询问完毕，然后因为我们在一个数组中存着较大数的编号，则我们只需要在那个数组里面进行递推，找出最大数的编号即可。最小数的寻找方法同理。

这个有点像分治的思想。

代码如下，仅供参考：
```
#include<cstdio>
#include<iostream>
using namespace std;
int t,n;
char s[5];
int sum,maxx[55],minn[55];
int main(){
	cin>>t;
	while(t--){
		sum=0;
		cin>>n;
		for(int i=1;i<n;i+=2){
			cout<<"? "<<i<<" "<<i+1<<"\n";
			fflush(stdout);
			cin>>s;
			if(s[0]=='>'){
			    maxx[sum]=i;
				minn[sum]=i+1;
			}
			else{
			    maxx[sum]=i+1;
				minn[sum]=i;
			}
			sum++;
		}
		if(n&1){
		    maxx[sum]=n;
			minn[sum]=n;
			sum++;
		}
		for(int i=1;i<sum;i++){
			cout<<"? "<<maxx[i-1]<<" "<<maxx[i]<<"\n";
			fflush(stdout);
			cin>>s;
			if(s[0]=='>'){
			    maxx[i]=maxx[i-1];
			}
			cout<<"? "<<minn[i-1]<<" "<<minn[i]<<"\n";
			fflush(stdout);
			cin>>s;
			if(s[0]=='<'){
				minn[i]=minn[i-1];
			}
		}
		cout<<"! "<<minn[sum-1]<<" "<<maxx[sum-1]<<"\n";
		fflush(stdout);
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：xwh_hh (赞：0)

注：在博客查看效果更佳。

这道题建议评橙，好像有一年 NOIP 普及组初赛出现过这题，我打模拟赛时错了，印象挺深刻。

好了，我们转入正题。  
首先，最无脑的方法莫过于一一比较，需要 $2n-2$ 次，显然不行。  

然后，我们可以将元素两两分组，多出一个或两个。  
对于每一组，我们举行一场组内 PK，大的一方进入争夺最大值赛，小的一方进入争夺最小值赛，打擂台法，组内 PK 加上打擂台，每组要 $3$ 次，要比 $3\times\lceil\frac{n}{2}-1\rceil=\lceil\frac{3n}{2}\rceil-3$ 次。  

现在问题来了，初始化咋办？  
- 如果分组完毕后只多出 $1$ 个，最大值和最小值初始值都为多余的这个元素；
- 如果多出两个，将它们进行比较，最大值初始化为大一点的元素，最小值初始化为小一点的元素即可。

反正不管怎么样，比较次数不会超过 $\lceil\frac{3n}{2}\rceil-2$ 次，可以 AC。  
最后强调一下，交互题最后输出 `endl` 会自动清除缓存。  
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char c;
void cmp(int a,int b){//一次比较 
	cout<<"? "<<a<<' '<<b<<endl;
	cin>>c;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int a,b;
		//初始化最大值，最小值 
		if(n%2==0){
			cmp(n-1,n);
			if(c=='>') a=n-1,b=n;
			else a=n,b=n-1; 
		}else{
			a=b=n;
		}
		//分组比较 
		for(int i=1;i<=n-2;i+=2){
			int u=i,v=i+1;
			cmp(u,v);
			if(c=='>'){//保证u<=v 
				swap(u,v);
			}
			cmp(a,v);
			if(c=='<') a=v;
			cmp(b,u);
			if(c=='>') b=u;
		}
		cout<<"! "<<b<<' '<<a<<endl;
	}
	return 0;
}
```

---

## 作者：xzggzh1 (赞：0)

题意：给出一个 $n$ 代表有 $n$ 个数字，你可以问下标为 $x$ 和 $y$ 的数的大小，会给出">"，"<"或"="，要求询问次数不能超过
 $\lceil\frac{3n}{2}\rceil-2 $ 次	
 ，最后输出最小的数和最大的数的下标。
 
 ---
 
是一道挺好的交互题。
 
我们可以利用分而治之的思想来解决这个问题，毕竟这个上限决定了算法的大致复杂度。
 
考虑将这么多数字分为两组，先两两比较，把大的分为一组，小的分为一组，最大值只会在大的一组里，最小值只会在小的一组里（显然）。

那么现在是不是只用了 $ \frac n 2$ 次就把问题的规模转换成了 $\frac n2$。

所以一直这么操作直到一组只剩下一个数字，复杂度正确。

---

核心代码：

```cpp
int cmp(int a, int b) {
	cout << "? " << a <<" "<< b << endl;
	char s;
	cin >> s;
	if (s=='>') return a;
	else return b;
}
int main () {
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		int min=n,max=n;
		if (n%2==0) {
			max=cmp(n,n-1);
			min=2*n-1-max;
		}
		n=(n-1)/2;
		for (int i=1;i<=n;i++) {
			int maxx,minn;
			maxx=cmp(2*i,2*i-1);
			minn=4*i-1-maxx;
			max=cmp(max,maxx);
			min=min+minn-cmp(min,minn);
		}
		cout << "! " << min << " " << max << endl;
	}
}
```

---

