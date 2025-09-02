# JOI 2006 本選 問題3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2006ho/tasks/joi2006ho_c



# 题解

## 作者：tbdsh (赞：1)

~~本蒟蒻第一篇题解~~
# Update
2022-10-19 题解发布。

2023-07-13 链接炸了，修复一下。
# 题意
[题目传送门](https://www.luogu.com.cn/problem/AT_joi2006ho_c)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-joi2006ho-c)

把一个自然数 $n$ 拆分成若干个 $ \le n$ 的正整数之和，序列中的数字**从大到小**排序，输出顺序也按照**字典序从大到小**输出。

其实这就是一道简单的搜索题，题意与[P2404](/problem/P2404)基本相同。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n;
int cnt[155];//cnt数组存储搜到的数字。
void dfs(int x, int sum){
  if (sum == n){//如果符合要求就输出。
    for (int i = 1; i < x - 1; i++){
      cout << cnt[i] << " ";
    }
    cout << cnt[x - 1] << "\n";
    return ;
  }else if (sum > n){//如果此时加起来的和已经大于 n 了就不用继续搜了，因为会越搜越大。
    return ;
  }
  for (int i = (cnt[x - 1] == 0 ? n : cnt[x - 1])/*三目运算符，第一次搜要从 0 开始，因为序列要递减，所以后一次搜索要从上一次搜到的数开始。*/; i >= 1; i--){
    cnt[x] = i;//当前的第 x 个数是 i。
    dfs(x + 1, sum + i);//搜索下一个数，当前搜到的和加上 i。
  }
}
int main(){
  cin >> n;
  dfs(1, 0);//从第一个数开始搜，初始和从 0 开始
  return 0;
}

```


---

## 作者：AirQwQ (赞：0)

## 前置不得不说的坑：行末不能有多余空格！！
## 入手
- 很基础的 dfs 板子题，和 [P2404](https://www.luogu.com.cn/problem/P2404) 基本一样。

## 思路

- 用一个 $ sum $ 变量储存和，当其等于 $ n $ 时输出即可。

## 实现の优化

- 在函数内多增一个 $ cnt $ 变量方便输出。

- ```for(int i=min(n-sum,plan[cnt-1]);i>=1;i--)``` 搜索时 ```i```  可以设置为 ```min(n-sum,plan[cnt-1])``` 少判断情况给程序加速。

- ```dfs(sum+i,cnt+1);``` 就可以少写两行回溯啦~（不仅是好写也能少一些运算为程序加速）。

## AcCode
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,plan[105];
void dfs(int sum,int cnt){
	if(sum==n){//因为分支情况时已经保证不会大于n，所以不用判断超过n。
		for(int i=1;i<cnt-1;i++)
			cout<<plan[i]<<' ';
		cout<<plan[cnt-1]<<endl;
		return ;
	}
	for(int i=min(n-sum,plan[cnt-1]);i>=1;i--){
		plan[cnt]=i;
		dfs(sum+i,cnt+1);
	}
}
int main(){
    cin>>n;
    plan[0]=n;//第0个要初始化。
    dfs(0,1);//cnt从零开始会RE。
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道简单的不要不要的最基础的 $\text{dfs}$ 练习题。

题目灰常简单：输入一个不超过 $30$ 的正整数 $n$，输出 $n$ 的所有拆分方法（保证相邻的两个数，第一个数不小于第二个数）。

样例输入：

```cpp
5
```

样例输出：

```cpp
5
4 1
3 2
3 1 1
2 2 1
2 1 1 1
1 1 1 1 1
```

下面就是 $\text{dfs}$ 的方法：

从 $n$ 开始枚举，每一次在函数中使用递归枚举下去：`dfs(a - i, i)`，直到第一个参数 $a = 0$，输出拆分方法。 

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

vector <int> ccf; // vector 好东西
void dfs(int a, int b){
    if (!a){ // 输出
        for (int i = 0; i < ccf.size() - 1; i ++) cout << ccf[i] << ' ';
        cout << ccf.back() << '\n'; // 注意最后不能有空格
        return;
    }
    for (int i = min(a, b); i >= 1; i --)
        ccf.push_back(i), dfs(a - i, i), ccf.pop_back(); // 加入元素，递归，删除元素，经典dfs模板
}

int main(){
    int n;
    cin >> n;
    dfs(n, n); // dfs
    return 0;
}
```

谢谢大家，QwQ

---

## 作者：AlicX (赞：0)

#### 此题是一道深搜模板题，适合大家练手

没学过深搜的同学看这里->[深搜](https://blog.csdn.net/Huberyxiao/article/details/105017214?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166306557716800182741670%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166306557716800182741670&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-105017214-null-null.142^v47^body_digest,201^v3^control&utm_term=%E6%B7%B1%E6%90%9C&spm=1018.2226.3001.4187)

#### 具体思路
我们知道，深搜是一种不撞南墙不回头的算法，而我们这道题就是枚举每一个数，记录他们的和，继续枚举下去，直到和超出 $n$ 为止。观察样例，题目说按字典序大的顺序输出，我们可以发现当前这个数一定不会大于前一个数和 $n$ 减去当前和的最小值，那么思路就十分明显了，在 dfs 中定义三个状态，$s$ 代表当前数字之和，$k$ 代表当前选到第几个数字了，$last$ 表示上一次所选的数。递归出口：当 $s$ 大于 $n$ 时结束，$s$ 等于 $n$ 时输出，这里注意行末不能有空格。看看代码消化一下吧。

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=110;
int n;
int a[N];//答案数组 
void dfs(int s,int k,int last){//s 代表和，k 代表当前选到第几个数了，last 代表上一次所选的数字  
	if(s>n) return ;//当和大于n时结束递归 
	if(s==n){//找到了一组方案 
		for(int i=1;i<k-1;i++) cout<<a[i]<<" ";//行末无空格 
		cout<<a[k-1]<<endl;
		return ;
	}
	for(int i=min(n-s,last);i>=1;i--) a[k]=i,dfs(s+i,k+1,i);
    	//当前所选的数不能大于n-s的和或上一次所选的数，a[k]代表当前位置的数  
}
signed main(){
	cin>>n;
	a[0]=n;//边界 
	dfs(0,1,n);//开始时和为 0，选第一个数，上一次所选数字为 n 
	return 0;
}
```
$$Thanks$$

---

