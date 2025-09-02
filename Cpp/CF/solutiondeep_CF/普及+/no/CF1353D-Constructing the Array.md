# 题目信息

# Constructing the Array

## 题目描述

You are given an array $ a $ of length $ n $ consisting of zeros. You perform $ n $ actions with this array: during the $ i $ -th action, the following sequence of operations appears:

1. Choose the maximum by length subarray (continuous subsegment) consisting only of zeros, among all such segments choose the leftmost one;
2. Let this segment be $ [l; r] $ . If $ r-l+1 $ is odd (not divisible by $ 2 $ ) then assign (set) $ a[\frac{l+r}{2}] :=         i $ (where $ i $ is the number of the current action), otherwise (if $ r-l+1 $ is even) assign (set) $ a[\frac{l+r-1}{2}] := i $ .

Consider the array $ a $ of length $ 5 $ (initially $ a=[0,       0, 0, 0, 0] $ ). Then it changes as follows:

1. Firstly, we choose the segment $ [1; 5] $ and assign $ a[3] := 1 $ , so $ a $ becomes $ [0, 0, 1, 0, 0] $ ;
2. then we choose the segment $ [1; 2] $ and assign $ a[1] :=         2 $ , so $ a $ becomes $ [2, 0, 1, 0, 0] $ ;
3. then we choose the segment $ [4; 5] $ and assign $ a[4] :=         3 $ , so $ a $ becomes $ [2, 0, 1, 3, 0] $ ;
4. then we choose the segment $ [2; 2] $ and assign $ a[2] :=         4 $ , so $ a $ becomes $ [2, 4, 1, 3, 0] $ ;
5. and at last we choose the segment $ [5; 5] $ and assign $ a[5] := 5 $ , so $ a $ becomes $ [2, 4, 1, 3, 5] $ .

Your task is to find the array $ a $ of length $ n $ after performing all $ n $ actions. Note that the answer exists and unique.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
1 
1 2 
2 1 3 
3 1 2 4 
2 4 1 3 5 
3 4 1 5 2 6```

# AI分析结果

### 题目翻译
## 构造数组

### 题目描述
给定一个长度为 $n$ 的数组 $a$，其初始元素均为 0。你需要对这个数组进行 $n$ 次操作，在第 $i$ 次操作时，按以下步骤进行：
1. 选择长度最大的、仅由 0 组成的子数组（连续子段），若存在多个长度相同的子数组，则选择最左边的那个；
2. 设该子数组为 $[l; r]$。若 $r - l + 1$ 为奇数（不能被 2 整除），则将 $a[\frac{l + r}{2}]$ 赋值为 $i$（其中 $i$ 是当前操作的编号）；否则（若 $r - l + 1$ 为偶数），将 $a[\frac{l + r - 1}{2}]$ 赋值为 $i$。

以长度为 5 的数组 $a$（初始时 $a = [0, 0, 0, 0, 0]$）为例，其变化过程如下：
1. 首先，选择区间 $[1; 5]$，并将 $a[3]$ 赋值为 1，此时 $a$ 变为 $[0, 0, 1, 0, 0]$；
2. 接着，选择区间 $[1; 2]$，并将 $a[1]$ 赋值为 2，此时 $a$ 变为 $[2, 0, 1, 0, 0]$；
3. 然后，选择区间 $[4; 5]$，并将 $a[4]$ 赋值为 3，此时 $a$ 变为 $[2, 0, 1, 3, 0]$；
4. 再选择区间 $[2; 2]$，并将 $a[2]$ 赋值为 4，此时 $a$ 变为 $[2, 4, 1, 3, 0]$；
5. 最后，选择区间 $[5; 5]$，并将 $a[5]$ 赋值为 5，此时 $a$ 变为 $[2, 4, 1, 3, 5]$。

你的任务是找出经过 $n$ 次操作后长度为 $n$ 的数组 $a$。注意，答案是存在且唯一的。

你需要处理 $t$ 组独立的测试数据。

### 样例 #1
#### 输入
```
6
1
2
3
4
5
6
```
#### 输出
```
1 
1 2 
2 1 3 
3 1 2 4 
2 4 1 3 5 
3 4 1 5 2 6
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟题目中对数组的操作过程，关键在于如何高效地找到每次操作时最长且最左边的全 0 子数组。大部分题解使用优先队列来维护区间，每次取出队首元素（即最长且最左的区间）进行操作，然后将分割后的小区间重新加入优先队列。osfly 的题解使用线段树来维护区间信息，实现相对复杂，但也能完成任务。

### 所选的题解
- **tbdsh（4星）**
  - 关键亮点：思路清晰，代码简洁，使用优先队列实现模拟过程，对优先队列的比较运算符重载解释详细。
- **Strelitzia（4星）**
  - 关键亮点：代码结构清晰，使用自定义的输入输出模板，对优先队列的使用和区间处理逻辑明确。
- **几何之舞丶（4星）**
  - 关键亮点：对区间的奇偶性判断和处理逻辑详细，使用优先队列封装结构体实现模拟。

### 重点代码
#### tbdsh 的题解
```cpp
struct Node{
  int l, r;
  bool operator<(const Node &i)const{
    return r - l + 1 == i.r - i.l + 1 ? l > i.l : r - l + 1 < i.r - i.l + 1;
  }
};

void Solve(){
  for (int i = 1; i <= n; i++){
    a[i] = 0;
  }
  int cnt = 1;
  cin >> n;
  priority_queue<Node> b;
  b.push({1, n});
  while (b.size()){
    auto x = b.top();
    b.pop();
    if (x.l > x.r){
      continue;
    }
    int mid = (x.l + x.r) >> 1;
    a[mid] = cnt++;
    b.push({x.l, mid - 1});
    b.push({mid + 1, x.r});
  }
  for (int i = 1; i <= n; i++){
    cout << a[i] << " \n"[i == n];
  }
}
```
核心实现思想：定义一个 `Node` 结构体表示区间，重载小于运算符，使优先队列能按区间长度和左端点排序。在 `Solve` 函数中，先将整个数组区间加入优先队列，然后不断取出队首元素，找到中间位置赋值，再将分割后的小区间加入队列，直到队列为空。

#### Strelitzia 的题解
```cpp
struct node {
	int l,r,len;
	bool operator < (const node &x) const {
		if (len == x.len) return l > x.l;
		else return len < x.len;
	}
};

const int maxn = 2e5;

priority_queue<node> q;

int times,n,a[maxn];

int main () {
	read(times);
	while (times --) {
		read(n);
		q.push(node{1,n,n - 1 + 1});
		for (int i = 1 ; i <= n ; ++ i) {
			node now = q.top();
			q.pop();
			int mid = (now.l + now.r) >> 1;
			a[mid] = i;
			q.push(node{now.l,mid - 1,(mid - 1 - now.l + 1)});
			q.push(node{mid + 1,now.r,(now.r - (mid + 1) + 1)});
		}
		for (int i = 1 ; i <= n ; ++ i) {
			print(a[i]),putchar(' ');
		}
		putchar('\n');
	}
	return 0;
} 
```
核心实现思想：定义 `node` 结构体表示区间，重载小于运算符。在 `main` 函数中，处理多组数据，每次将整个数组区间加入优先队列，然后循环 $n$ 次，每次取出队首元素，找到中间位置赋值，再将分割后的小区间加入队列，最后输出结果。

#### 几何之舞丶的题解
```cpp
struct tmp1 //运算符重载<
{
    int x,id;
    tmp1(int a,int b) {x = a;id=b;}
    bool operator<(const tmp1& a) const
    {
        if(x==a.x)return id>a.id;
        return x<a.x;
    }
};
priority_queue<tmp1> s;
int a[200005];

signed main(){
    t=read();
    while(t--){
        n=read();
        memset(a,0,sizeof(a));//初始化
        s.push(tmp1(n,1));
        int step=1;
        while(!s.empty()){
            int l=s.top().id;
            int r=l+s.top().x-1;
            s.pop();
            if((l+r)%2){ //判断奇数偶数
                int mid=(l+r-1)>>1;
                a[mid]=step;step++;
                if(l==r)continue;
                if(l<mid)
                    s.push(tmp1(mid-l,l));
                if(mid<r)
                    s.push(tmp1(r-mid,mid+1));//压队列
            }
            else{
                int mid=(l+r)>>1;
                a[mid]=step;step++;
                if(l==r)continue;
                if(l<mid)
                    s.push(tmp1(mid-l,l));
                if(mid<r)
                    s.push(tmp1(r-mid,mid+1));
            }
        }
        for(int i=1;i<=n;i++)
            cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
} 
```
核心实现思想：定义 `tmp1` 结构体表示区间，重载小于运算符。在 `main` 函数中，处理多组数据，每次将整个数组区间加入优先队列，然后不断取出队首元素，根据区间长度的奇偶性找到中间位置赋值，再将分割后的小区间加入队列，最后输出结果。

### 最优关键思路或技巧
使用优先队列来维护区间，通过重载比较运算符，使得优先队列能自动按区间长度和左端点排序，每次取出队首元素进行操作，保证每次操作的都是最长且最左的区间，从而高效地模拟整个过程。

### 拓展思路
同类型题目可能会对操作规则进行变化，例如改变区间选择的条件、赋值的规则等，但核心思路仍然是模拟操作过程，可能需要使用不同的数据结构来维护信息。类似的算法套路包括使用优先队列、线段树等数据结构来维护区间信息，以实现对数组或序列的动态操作。

### 推荐洛谷题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
无

---
处理用时：62.91秒