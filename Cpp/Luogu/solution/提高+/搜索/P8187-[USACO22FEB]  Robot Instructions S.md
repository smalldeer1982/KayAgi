# [USACO22FEB]  Robot Instructions S

## 题目描述

Bessie 正在学习如何控制她最近收到的一个机器人。机器人从坐标平面上的点 $(0,0)$ 开始，Bessie 希望机器人最终停在点 $(x_g,y_g)$。Bessie 最初有一个包含 $N$ 条指令的列表（$1 \le N \le 40$），第 $i$ 条指令会将机器人向右移动 $x_i$ 个单位，向上移动 $y_i$ 个单位（当 $x_i$ 和 $y_i$ 为负数时，分别向左和向下移动）。对于每一个从 $1$ 到 $N$ 的 $K$，帮助 Bessie 计算她可以从原始 $N$ 条指令中选择 $K$ 条指令的方式数，使得在执行完这 $K$ 条指令后，机器人将停在点 $(x_g,y_g)$。注意：本题的时间和内存限制为 4 秒和 512MB，是默认值的两倍。

## 说明/提示

【样例解释】在这个例子中，有六种方式 Bessie 可以选择指令：
```
(-2,0) (3,0) (4,0) (0,10) (0,-10) (0,10) (1 2 3 5 6 7)
(-2,0) (3,0) (4,0) (0,10) (1 2 3 5)
(-2,0) (3,0) (4,0) (0,10) (1 2 3 7)
(5,0) (0,10) (0,-10) (0,10) (4 5 6 7)
(5,0) (0,10) (4 5)
(5,0) (0,10) (4 7)
```
对于第一种方式，机器人的路径如下：
```
(0,0) -> (-2,0) -> (1,0) -> (5,0) -> (5,10) -> (5,0) -> (5,10)
```

【数据范围】

- 测试用例 2-4 满足 $N \le 20$。
- 测试用例 5-16 不满足额外的约束条件。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
5 10
-2 0
3 0
4 0
5 0
0 10
0 -10
0 10```

### 输出

```
0
2
0
3
0
1
0```

# 题解

## 作者：tzyt (赞：32)

update： 2022/4/17 更正了博客地址

目录：
1. 暴力
2. 折半搜索 + map 或是哈希表
3. 折半搜索 + 双指针 + ~~和 dfs 不同~~奇怪的状态枚举方式
   1. 第一种双指针
   2. 第二种双指针
4. 完整代码

[题目链接](https://www.luogu.com.cn/problem/P8187)

[博客](https://ttzytt.com/2022/03/P8187/)中观看体验更佳

# 1. 题意
给你 $n$ 个二维的向量，对于任意一个 $k (1 \le k \le n)$，求出有多少选取的方案能满足在这 $n$ 个向量中选 $k$ 个，并且他们的和为 $(x_g, y_g)$。

#  2. 分析

## 2.1 暴力算法
看到这个题我们可以比较快的想到拿部分分的做法，就是暴力枚举所有的选取方案，然后看他们加起来是否等于目标向量，再把符合要求的方案累加到答案中。但是我们发现 $n = 40$，并且这个算法的复杂度是 $2^n$ 的，所以一定会超时。

## 2.2 折半搜索 + map 或者是哈希表
### 2.2.1 简要思路
这道题中的折半搜索指的是把 $n$ 种向量分成两部分，对这两个部分分别用暴力的方法求出所有可能的选取方案，再把这些选取的方案，以及这个方案的结果（他们的和）按照某种方案储存下来，最后匹配这两部分的方案，把符合题目要求的（和等于 $(x_g, y_g$）的）累加进答案里。

### 2.2.2 细节
要达到前面提到的效果，我们可以使用 STL 的 map 或者是 unordered_map （手写哈希表也可以，但是可能要花更多时间来实现）来储存每个选取的方案。这里推荐使用 unordered_map，因为 map 的时间复杂度是 $O(\log n)$ 的，在这道题中会被卡，而 unodered_map 和手写哈希表的理想时间复杂度是 $O(1)$（当然使用 unodered_map 的话也要确保哈希函数写得好才不会被卡，~~比如我现在写的就过不了~~）。

对于暴力枚举状态的部分，一般的方法是 dfs ，也比较好写，这篇题解的双指针部分讲了一个比较奇怪的方法，想看的可以跳到下面。

注：下文的 map 指 unodered_map 或是 map 或是 手写的哈希表

我们首先创建两个 map ，`fir` 和 `sec`，分别储存前半部分向量的选取方案和后半部分的选取方案。对于这两个 map 的键值，我们可以设成包含 $(\text{sum}_x, \text{sum}_y, k)$ 三个整数的结构体。其中 $(\text{sum}_x, \text{sum}_y)$ 表示当前这个方案下，选取的所有向量的和。$k$ 表示当前的这个方案一共选取了多少个向量。因为可能有很多方案的 $x,y,k$ 都完全一样，所以对于 map 的值，我们设置成 $(\text{sum}_x, \text{sum}_y, k)$ 这三个值都相同的方案数。

对于答案的储存，我们开一个 `ans[n]` 的数组，`ans[i]` 表示 $k = i$ 时的选取方案数。

找到两部分的方案后我们要把符合要求的方案组合累加到答案中。具体来说，每个在 map 中储存的方案都包含一个这个方案的向量和 $(\text{sum}_x, \text{sum}_y)$ 。 我们设一个从前半部分向量得到的方案的向量和为 $\vec{v_1}$ ， 一个后半部分方案的向量和为 $\vec{v_2}$ ，那么如果 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ ，我们就把这个方案记录进答案。

因为我们使用了 map ，所以并不需要真的用双层循环把每个方案都遍历一遍。我们知道对于一个可能的匹配方案 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ 。那么我们可以使用一个双层循环，一层枚举 fir 这个 map，一维枚举当前处理的 $k$ 。然后在循环里，我们可以写: 

`ans[当前k] += it_fir.值 * sec[{x_g - it_fir.键.x, y_g - it_fir.键.y, 当前k - it_fir.键.k}]`

其中 `it_fir` 指的是 fir 的迭代器。而 `sec[{x_g - it_fir.键.x, y_g - it_fir.键.y, 当前k - it_fir.键.k}]` 中的方案和 `it_fir` 遍历到的方案符合 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ ，并且这两种方案选取的向量数的和也等于当前 k 。因为这两个 map 的值是所有符合这些条件的方案的数量，所以我们把这两个值相乘以求出所有符合要求的匹配数量。

## 2.3 折半搜索 + 双指针
双指针的理论复杂度似乎是和哈希表一样的，但是如果哈希函数有问题的话，哈希表的速度就会慢很多。而双指针就没有这个问题。
### 2.3.1 双指针a
我们可以首先开两个 vector ，fir 和 sec ，其数据类型和之前 map 的一样，也是 $(\text{sum}_x, \text{sum}_y, k)$ 。fir 储存由前半部分的向量得来的方案，sec储存后半部分的。

枚举完所有方案后我们对这两个 vector 进行排序，排序规则如下：
```cpp
if(a.x != b.x) return x < b.x;
if(a.y != b.y) return y < b.y;
return a.k < b.k;
```

然后我们创建两个指针，$p_1$ 的初值设成 1， $p_2$ 的初值设成 `sec.size() - 1` ，代表 `sec` 的最后一个元素。此时 $p_1$ 指向的是 `fir` 中最小的元素，而 $p_2$ 指向 `sec` 中最大的元素。我们可以想一下，如果想要让当前的这两个指针所指的 $\vec{v_1}, \vec{v_2}$ 
的和等于 $(x_g, y_g)$ ，需要怎么做。如果我们想要增加 $\vec{v_1} + \vec{v_2}$ 的值，只能使 $p_1$ 增加，因为 $p_2$ 已经指向这个数组里最大的元素了。反过来也是一样的，如果我们想要减少 $\vec{v_1} + \vec{v_2}$ 的值，也只能使 $p_2$ 减少。写成程序就是下面这样：
```cpp
int p1 = 0, p2 = sec_half.size() - 1;
while(p1 < fir_half.size() && p2 >= 0){
   Instruct &f = fir_half[p1], &s = sec_half[p2];
   if(f.x + s.x < tar_x ||(f.x + s.x == tar_x && f.y + s.y < tar_y)){
      //如果两个向量相加小于目标值，我们只能加 p1 的值，
      //因为 p2 指向的元素最开始就是最大的。
      p1++;
   }
   else if(f.x + s.x > tar_x ||(f.x + s.x == tar_x && f.y + s.y > tar_y)){
      //如果两个向量相加大于目标值，我们只能减 p2 的值，
      //因为 p1 指向的元素最开始就是最小的。
      p2--;
   }
   //下面后半段代码插入的位置
}
```
注：`Instruct` 是包含 `{x, y, k}` 三种整数的结构体。

通过这样的方法，我们最终就一定能找到 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ 的情况。不过呢，这两个数组中都可能有连续的一段是完全一样的值，也就是有多个 $p_1$ , $p_2$ 满足 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ 。因此我们需要找出符合条件的这个连续段具体是什么。通过上面的代码，我们已经知道了，满足条件的最小 $p_1$ 和最大的 $p_2$，因为我们希望找出连续段的具体范围，所以还需要找出最大的 $p_1$ 和最小的 $p_1$ 。那么如何找呢？很简单，因为连续的这一段值一定都完全相等，所以我们只需要判断当前元素是否和最开始的元素相等就可以了。

当然，因为我们还需要把符合的匹配统计进答案，而答案是按照 $k$ 来输出的。所以我们可以开两个数组 `fir_same_k` 和 `sec_same_k` 。`fir_same_k[i]` 就表示，对于第一个数组，在符合条件的这一长段中， $k = i$ 的有多少。而 `sec_same_k` 是对于第二个数组的。

然后我们就可以得到下面的代码了：

注意这段代码是插入前面那段代码的 `else if` 后面的
```cpp
else{
   int p1t, p2t;
   
   memset(fir_same_k, 0, sizeof(fir_same_k));
   memset(sec_same_k, 0, sizeof(sec_same_k));
   
   //因为每次找到的符合条件的段都是不重合的，所以每次都清空一下数组

   for(p1t = p1; p1t < fir_half.size() && fir_half[p1t] == f; p1t++){
      //p1t 代表能满足 v_1 + v_2 == (x_g, y_g) 的最大 p1
      fir_same_k[fir_half[p1t].k]++;
   }
   for(p2t = p2; p2t >= 0 && sec_half[p2t] == s; p2t--){
      //p2t 代表满足 v_1 + v_2 == (x_g, y_g) 的最小 p2
      sec_same_k[sec_half[p2t].k]++;
   }

   //统计答案，对于前半段和后半段都枚举可能的
   for(int i = 0; i <= 20; i++){
      for(int j = 0; j <= 20; j++){//这个20其实是可以改成 n / 2 + 1 的
         ans[i + j] += 1LL * fir_same_k[i] * sec_same_k[j];
         //相乘是因为同一个 fir_same_k[i] 和 sec_same_k[j] 
         //中代表的任意一种选取方案都是完全相同的，(x,y,k) 都相同
      }
   }
   p1 = p1t, p2 = p2t;//不加这个会一直在相同的一段死循环
}
```

这个方法还是跑的相对比较快的，可以看下[提交记录](https://www.luogu.com.cn/record/71008837)

### 2.3.2 双指针 b
我们发现双指针 a 的方法会需要在统计答案时开 `fir_same_k` 和 `sec_same_k` 这两个数组来统计 $k$ 相同的情况。我们其实可以改进一下这个方法，直接在枚举状态的时候把 $k$ 相同的方案放到一起。

具体来说，我们把前面的 `fir` 和 `sec` 这两个 vector 改成 `vector<Instruct> fir[20], sec[20]` 。`fir[i]` 就储存前半部分 $k = i$ 时的所有方案，`sec[i]` 是后半部分的。既然把储存方案的方法改了，后面的双指针部分自然也要改。

这一次我们需要用一个双重循环来分别枚举不同的 `fir[i]` 和 `sec[j]`。在循环内部我们再做和双指针 a 相似的事情。也就是说，我们已经知道了当前前半部分的方案和后半部分的方案的 $k$，现在只需要通过双指针找出能满足 $\vec{v_1} + \vec{v_2} = (x_g, y_g)$ 的 $p_1$ 和 $p_2$ 范围。

```cpp
for(int fir_k = 0; fir_k <= n / 2 + 1; fir_k++){   //枚举当前前半部分的 k
   for(int sec_k = 0; sec_k <= n / 2 + 1; sec_k++){//枚举后半部分的 k
      int p1 = 0, p2 = sec_half[sec_k].size() - 1;
      while(p1 < fir_half[fir_k].size() && p2 >= 0){
         Instruct &f = fir_half[fir_k][p1], &s = sec_half[sec_k][p2];
         if(f.x + s.x < tar_x ||(f.x + s.x == tar_x && f.y + s.y < tar_y)){
            p1++;
            //找出当前 fir_k 时满足 v_1 + v_2 == (x_g, y_g) 的最小的 p1
         }
         else if(f.x + s.x > tar_x ||(f.x + s.x == tar_x && f.y + s.y > tar_y)){
            p2--;
            //找出当前 sec_k 时满足 v_1 + v_2 == (x_g, y_g) 的最大 p2
         }
         else{
            int p1t = p1, p2t = p2;
            while(p1t < fir_half[fir_k].size() && fir_half[fir_k][p1t] == f){
               p1t++;
            }
            while(p2t >= 0 && sec_half[sec_k][p2t] == s){
               p2t--;
            }
            
            ans[fir_k + sec_k] += 1LL * (p1t - p1) * (p2 - p2t); 
            //把 p1 范围长度乘上 p2 范围的长度
            //小细节：本来要表示长度的话应该是 p1t - p1 + 1的，但是我们可以观察前面两个while
            //        在跳出之后 p1t 会比正确的 p1t 多 1，而 p2t 会比正确的 p2t 少1，因为如果
            //        它们还是正确的话会又回到循环中。因我们计算长度的时候就不需要 + 1 了。
            p1 = p1t, p2 = p2t;
         }
      }
   }
}
```
那么双指针b的写法比a有什么好处呢？答案就是节省空间。如果我们使用的是双指针a，那储存方案的结构体必须包含 $x, y, k$ 三种整数。注意其中的 $k$ 最大只有 $20$，而我们却必须开一个 `int` 或是 `short` 来储存这个值，考虑到 $20$ 这个值非常小，不管哪种数据类型都会浪费大量的空间。而采用双指针b后，我们的结构体中只会包含 $x, y$ 两种整数， $k$ 这个值储存在数组的下标中，只要你开的数组大小为 $k$ 的最大值，就不会有任何的浪费。

具体的对比可以参考这个[提交记录](https://www.luogu.com.cn/record/71362478)，可以发现相比双指针 a 的做法，双指针 b 的内存占用大约少了 17MB 左右

当然，代价也是有的，双指针 b 会稍微慢一些。我估计这主要出在双指针的环节。排序的部分甚至还会快一点。当然，不管哪种双指针，他们的理论复杂度都是一样的，因为每一种选取方案最多会被遍历到一次。


## 2.4 奇怪的状态枚举方法
这道题中常见的状态枚举方法就是 dfs。这里提供一种比较奇怪的枚举方法。在一个选取方案中，对于每个向量，都有两种状态，选或者是不选。因为只有选或不选两种状态，我们可以想到通过二进制数字表示这个状态。数字的第 $i$ 位表示向量 $i$ 是选还是不选，例如：$(101)_2$ 就表示选择第 1 ，3 个向量，不选第 2 个。要枚举所有的状态，我们只需要把一个数从 $0$ 一直累加到 $2^n$ 就可以了，并且每次累加的时候检查他每一位是 0 还是 1 。当然，因为我们这里采用的是折半搜索，所以只需要累加到 $2^\frac{n}{2}$。

至于复杂度的话，可能比 dfs 还慢？而且码量更大？毕竟每次累加还要写一个循环把这个数字从第一位检查到第二十位。不过，因为不需要递归，所以不需要一直给递归的函数开栈，内存占用可能会少一些。

真在比赛的时候还是不建议这样写的，毕竟 dfs 写起来是真的方便，这里只是提供一种好玩的做法。

# 3. 完整代码
## 3.1 折半搜索 + 哈希表
这个做法一直在调，现在也没卡过时间和空间限制，应该是我哈希函数写挂了，但是我也不知道正确的写法是怎么样的，如果想用这个做法，可以看其它大佬的题解。如果你会这个方法，而且能帮我调一下的话我表示非常感谢，这是[提交记录](https://www.luogu.com.cn/record/71362564)，代码我放在[这里](https://www.luogu.com.cn/paste/081u2pfp)了。
## 3.2 折半搜索 + 双指针a + 二进制枚举方法
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rg register
const int MAXN = 45;

struct Instruct{
    ll x, y;
    int k;
    const bool operator < (Instruct b) const{
        if(x != b.x) return x < b.x;
        if(y != b.y) return y < b.y;
        return k < b.k;
    }
    const bool operator == (Instruct b) const{
        return x == b.x && y == b.y;
    }
}ins[MAXN];

vector<Instruct> fir_half, sec_half;
ll ans[MAXN];
int mx_state;
int n;
int tar_x, tar_y;

void vec_sum(int st, int ed, int cur_state, vector<Instruct> *cur_half){
    //根据当前提供的状态 cur_state, 把选中的向量累加起来
    //因为整个搜索的过程分成了两部分，所以需要参数表示是哪个部分，st， ed 表示的就是参与搜索的第一份向量，和最后一个。
    ll tot_x = 0, tot_y = 0;
    int k = 0;
    int len = ed - st + 1;
    for(int i = 1; i <= len; i++){
        if(cur_state & (1 << (i - 1))){
            tot_x += ins[st + i - 1].x, tot_y += ins[st + i - 1].y;
            k++;
        }
    }
    (*cur_half).push_back({tot_x, tot_y, k});
}

void state_generator(bool mode){
    //mode 表示当前处理的是前半部分还是后半部分，0是前半部分，1是后半部分
    rg int cur_state = 0;//初始的状态，对应的就是什么都不选
    int st, ed;
    vector<Instruct> *cur_half;//fir_half和sec_half储存这前半部分的方案和后半部分的方案
                               //cur_half就是当前这次搜索要把方案存到哪里
    if(mode){
        cur_half = &sec_half;
        st = n / 2 + 1, ed = n;
        if(n & 1) mx_state = mx_state * 2 + 1;
        //mx_state就是表示状态的数字最大能达到多少，它的初始值是 2^(n/2) 但是如果 n 是奇数
        //后半部分会比前半部分多包含一个向量，所以还要把原来的 mx_state * 2 + 1
    }
    else{
        cur_half = &fir_half;
        st = 1, ed = n / 2;
    }

    while(cur_state <= mx_state){
        vec_sum(st, ed, cur_state, cur_half);
        cur_state++;
    }
}

int main(){
    scanf("%d%d%d", &n, &tar_x, &tar_y);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld",&ins[i].x, &ins[i].y); 
    }
    for(int i = 0; i < n / 2; i++){
        mx_state = mx_state | (1 << i);
        //最大的状态是 n/2 位都是 1
    }
    state_generator(0); state_generator(1);
    
    sort(fir_half.begin(), fir_half.end());
    sort(sec_half.begin(), sec_half.end());

    rg int p1 = 0, p2 = sec_half.size() - 1;
    int fir_same_k[21], sec_same_k[21];

   while(p1 < fir_half.size() && p2 >= 0){
        Instruct &f = fir_half[p1], &s = sec_half[p2];
        if(f.x + s.x < tar_x ||(f.x + s.x == tar_x && f.y + s.y < tar_y)){
            //如果两个向量相加小于目标值，我们只能加 p1 的值，
            //因为 p2 指向的元素最开始就是最大的。
            p1++;
        }
        else if(f.x + s.x > tar_x ||(f.x + s.x == tar_x && f.y + s.y > tar_y)){
            //如果两个向量相加大于目标值，我们只能减 p2 的值，
            //因为 p1 指向的元素最开始就是最小的。
            p2--;
        }
        else{
            int p1t, p2t;
            memset(fir_same_k, 0, sizeof(fir_same_k));
            memset(sec_same_k, 0, sizeof(sec_same_k));
            //因为每次找到的符合条件的段都是不重合的，所以每次都清空一下数组
            for(p1t = p1; p1t < fir_half.size() && fir_half[p1t] == f; p1t++){
                //p1t 代表能满足 v_1 + v_2 == (x_g, y_g) 的最大 p1
                fir_same_k[fir_half[p1t].k]++;
            }
            for(p2t = p2; p2t >= 0 && sec_half[p2t] == s; p2t--){
                //p2t 代表满足 v_1 + v_2 == (x_g, y_g) 的最小 p2
                sec_same_k[sec_half[p2t].k]++;
            }
            //统计答案，对于前半段和后半段都枚举可能的
            for(int i = 0; i <= 20; i++){
                for(int j = 0; j <= 20; j++){//这个20其实是可以改成 n / 2 + 1 的
                    ans[i + j] += 1LL * fir_same_k[i] * sec_same_k[j];
                    //相乘是因为同一个 fir_same_k[i] 和 sec_same_k[j] 
                    //中代表的任意一种选取方案都是完全相同的，(x,y,k) 都相同
                }
            }
            p1 = p1t, p2 = p2t;//不加这个会一直在相同的一段死循环
        }        
    }

    for(int i = 1; i <= n; i++){
        printf("%lld\n", ans[i]);
    }
    system("pause");
}
```
## 3.2 折半搜索 + 双指针b + 二进制枚举方法
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rg register
const int MAXN = 45;

struct Instruct{
    ll x, y;
    const bool operator < (Instruct b) const{
        if(x != b.x) return x < b.x;
        return y < b.y;
    }
    const bool operator == (Instruct b) const{
        return x == b.x && y == b.y;
    }
}ins[MAXN];
vector<Instruct> fir_half[MAXN], sec_half[MAXN];
ll ans[MAXN];
int mx_state;
int n;
int tar_x, tar_y;

void vec_sum(int st, int ed, int cur_state, vector<Instruct> *cur_half){
    //根据当前提供的状态 cur_state, 把选中的向量累加起来
    //因为整个搜索的过程分成了两部分，所以需要参数表示是哪个部分，st， ed 表示的就是参与搜索的第一份向量，和最后一个。
    ll tot_x = 0, tot_y = 0;
    int k = 0;
    int len = ed - st + 1;
    for(int i = 1; i <= len; i++){
        if(cur_state & (1 << (i - 1))){
            tot_x += ins[st + i - 1].x, tot_y += ins[st + i - 1].y;
            k++;
        }
    }
    cur_half[k].push_back({tot_x, tot_y});
}

void state_generator(bool mode){
    //mode 表示当前处理的是前半部分还是后半部分，0是前半部分，1是后半部分
    rg int cur_state = 0;//初始的状态，对应的就是什么都不选
    int st, ed;
    vector<Instruct> *cur_half;
    if(mode){ 
        cur_half = sec_half;
        st = n / 2 + 1, ed = n;
        if(n & 1) mx_state = mx_state * 2 + 1;
        //mx_state就是表示状态的数字最大能达到多少，它的初始值是 2^(n/2) 但是如果 n 是奇数
        //后半部分会比前半部分多包含一个向量，所以还要把原来的 mx_state * 2 + 1
    }
    else{
        cur_half = fir_half;
        st = 1, ed = n / 2;
    }

    while(cur_state <= mx_state){
        vec_sum(st, ed, cur_state, cur_half);
        cur_state++;
    }
}

int main(){
    scanf("%d%d%d", &n, &tar_x, &tar_y);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld",&ins[i].x, &ins[i].y); 
    }
    for(int i = 0; i < n / 2; i++){
        mx_state = mx_state | (1 << i);
        //最大的状态是 n/2 位都是 1
    }
    state_generator(0); state_generator(1);
    
    for(int i = 0; i <= n / 2 + 1; i ++){
        sort(fir_half[i].begin(), fir_half[i].end());
        sort(sec_half[i].begin(), sec_half[i].end());
    }

    for(int fir_k = 0; fir_k <= n / 2 + 1; fir_k++){   //枚举当前前半部分的 k
        for(int sec_k = 0; sec_k <= n / 2 + 1; sec_k++){//枚举后半部分的 k
            int p1 = 0, p2 = sec_half[sec_k].size() - 1;
            while(p1 < fir_half[fir_k].size() && p2 >= 0){
                Instruct &f = fir_half[fir_k][p1], &s = sec_half[sec_k][p2];
                if(f.x + s.x < tar_x ||(f.x + s.x == tar_x && f.y + s.y < tar_y)){
                    p1++;
                    //找出当前 fir_k 时满足 v_1 + v_2 == (x_g, y_g) 的最小的 p1
                }
                else if(f.x + s.x > tar_x ||(f.x + s.x == tar_x && f.y + s.y > tar_y)){
                    p2--;
                    //找出当前 sec_k 时满足 v_1 + v_2 == (x_g, y_g) 的最大 p2
                }
                else{
                    int p1t = p1, p2t = p2;
                    while(p1t < fir_half[fir_k].size() && fir_half[fir_k][p1t] == f){
                    p1t++;
                    }
                    while(p2t >= 0 && sec_half[sec_k][p2t] == s){
                    p2t--;
                    }
                    
                    ans[fir_k + sec_k] += 1LL * (p1t - p1) * (p2 - p2t); 
                    //把 p1 范围长度乘上 p2 范围的长度
                    //小细节：本来要表示长度的话应该是 p1t - p1 + 1的，但是我们可以观察前面两个while
                    //        在跳出之后 p1t 会比正确的 p1t 多 1，而 p2t 会比正确的 p2t 少1，因为如果
                    //        它们还是正确的话会又回到循环中。因我们计算长度的时候就不需要 + 1 了。
                    p1 = p1t, p2 = p2t;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%lld\n", ans[i]);
    }
    system("pause");
}

```
最后，希望这篇题解对你有帮助。有任何问题都可以在私信和评论区提出，我会尽量解决问题。

---

## 作者：宇宙的怒火 (赞：7)

考场上想到双向搜索了，但不会存状态，最后只过了 5 个点。
看了官方题解，才明白可以把搜索到的状态存入一个数组，最后将这两个数组的状态进行筛选。


------------
步入正题。
看到题目，就想到要搜索，对于每一种操作只有两种可能：进行操作和不进行操作。爆搜代码很简单 
```cpp
void dfs(int pos,int x,int y,int k){
//该处理第pos操作,现在坐标为(x,y),已经进行了k个操作
	if(pos==n+1){
   		if(x==xg&&y==yg)ans[k]++;
   		return;
   	}
	dfs(pos+1,x,y,k);//不进行该操作
	dfs(pos+1,x+mx[pos],y+my[pos],k+1);//进行该操作
}
``` 
不难看出，这一共会搜索到  $  2^n  $  个状态。对于 $ n<=20 $ ，这是没有问题的。但当 $ n=40 $ 时，就会 $ 2^{40}  = 1,099,511,627,776  $  。这显然不行。由于起点和终点已知，想到双向搜索，这样复杂度就会为 $ 2 * 2^{n/2}  $  , $  2 * 2^{20} = 2,097,152 $  明显优于前者

那么我们可以有一下思路（与官方题解思路有差别）：

- 先从( 0 , 0 )开始对前 $ n/2 $ 个操作进行搜索，得到了经过这 $ n/2 $ 个操作后可能到达的 node (包括坐标和操作数)的序列 e1
- 再从( xg , yg )即终点坐标开始对剩下的操作进行反向搜索，又得到了可能到达的 node 的序列 e2 
-  e1 与 e2 中一对坐标相同的 node 即为一个合法的解,得到两者操作数的和k，使 ans [ k ]++

然后：[结果](https://www.luogu.com.cn/record/70679098)

啊这，忙乎半天，一点用没有

别急。因为有一种东西，叫排序。

可以让 e2 的坐标的 x 从小到大排序， x 相等的让 y 从小到大排序，配合上二分查找，就可以大大减少所需的时间



当找到相等的坐标时，就从这里向两边延伸 extend ，把所有相等的坐标都收入囊中

然而， T 了两个点。。。

经测试，发现 extend 占用了大量时间，原因是会有很多坐标和操作数均相等的 node ，我们只能将它一个一个的拿进来。所以我们要将它们合并，好一把拿住它们。

合并要求：坐标相等，操作数相等

[结果](https://www.luogu.com.cn/record/70693087)

总代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1<<21
#define ll long long
ll n,mx[41],my[41],nn,cnt1,cnt2,cnt3,ans[41];
struct point{
	ll x,y;
	friend bool operator==(point a,point b){
		return a.x==b.x&&a.y==b.y;
	}
}goal;
struct node{
	point a;
	int num,pos;
	node operator+(int k){
		return (node){(point){a.x+mx[k],a.y+my[k]},num+1,0};
	}
	node operator-(int k){
		return (node){(point){a.x-mx[k],a.y-my[k]},num+1,0};
	}
}e1[N],e2[N],e3[N];
bool cmp(node a,node b){
	if(a.a==b.a){
		if(a.num!=b.num)return a.num<b.num;
		return a.pos<b.pos;
	}
	if(a.a.x!=b.a.x)return a.a.x<b.a.x;
	return a.a.y<b.a.y;
}
void dfs1(node a,int k){
	if(k==nn+1){
		a.pos=++cnt1;
		e1[cnt1]=a;
		return;
	}
	dfs1(a,k+1);
	dfs1(a+k,k+1);
}
void dfs2(node a,int k){
	if(k==nn){
		a.pos=++cnt2;
		e2[cnt2]=a;
		return;
	}dfs2(a,k-1);
	dfs2(a-k,k-1);
}
void extend(int x,node a){
	int p=x;
	while(a.a==e3[p].a){
		ans[a.num+e3[p].num]+=e3[p].pos;
		p--;
	}p=x+1;
	while(a.a==e3[p].a){
		ans[a.num+e3[p].num]+=e3[p].pos;
		p++;
	}
}
void work(node a){
	ll x=a.a.x;
	int l=1,r=cnt3,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(e3[mid].a.x<x)l=mid+1;
		else if(e3[mid].a.x>x)r=mid-1;
		else {
			if(e3[mid].a.y>a.a.y)r=mid-1;
			else if(e3[mid].a.y<a.a.y)l=mid+1;
			else {
				extend(mid,a);
				return;
			}
		}
	}
}
int main(){
	cin>>n>>goal.x>>goal.y;
	nn=n/2;
	for(int i=1;i<=n;i++){
		cin>>mx[i]>>my[i];
	}dfs1((node){(point){0,0},0,0},1);
	dfs2((node){goal,0,0},n);
	sort(e2+1,e2+cnt2+1,cmp);
    e3[++cnt3]=e2[1];
    e3[cnt3].pos=1;
    for(int i=2;i<=cnt2;i++){
	    if(!(e2[i].a==e3[cnt3].a)||e2[i].num!=e3[cnt3].num){
		    e3[++cnt3]=e2[i];
		    e3[cnt3].pos=1;
	    }else{
		    e3[cnt3].pos++;
	    }
    }
	for(int i=1;i<=cnt1;i++){
		work(e1[i]);
	}for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl;
	}return 0;
}
```


---

## 作者：I_am_Accepted (赞：4)

### Preface

妈妈再也不用担心我使用 `unordered_map` 了，因为被卡。

### Analysis

由于 $2^N$ 接受不了，而 $2^{N/2}$ 可以，想到 meet in middle。

处理出只但不必全使用前一半的指令能到达的位置和需要的步数，同理处理出哪些点使用后一半指令能够到达终点 $g$（也就是说从 $g$ 倒着处理）。

这样两部分点集数量均为 $2^{20}$，我们将他们按平面上的位置排序（任意偏序关系），只有两个点集中同一位置上的点才能构成答案。使用双指针即可 AC。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define int long long
#define Pos pair<int,int>
#define Tup pair<Pos,int>
#define N 50
const int inf=1e18;
Pos a[N],t,tar=mkp(inf,inf);
int cnt[N],ans[N];
vector<Tup> b,c,cur;
int gap,n;
inline Tup mkt(int x,int y,int z){return mkp(mkp(x,y),z);}
signed main(){IOS;
	cin>>n;
	cin>>t.fir>>t.sec;
	For(i,1,n) cin>>a[i].fir>>a[i].sec;
	gap=n>>1;
	b.pb(mkt(0,0,0));
	For(i,1,gap){
		cur.clear();
		for(auto j:b) cur.pb(mkt(j.fir.fir+a[i].fir,j.fir.sec+a[i].sec,j.sec+1));
		for(auto j:cur) b.pb(j);
	}
	sort(b.begin(),b.end());
	c.pb(mkp(t,0));
	For(i,gap+1,n){
		cur.clear();
		for(auto j:c) cur.pb(mkt(j.fir.fir-a[i].fir,j.fir.sec-a[i].sec,j.sec+1));
		for(auto j:cur) c.pb(j);
	}
	sort(c.begin(),c.end());
	auto it=c.begin();
	for(auto i:b){
		if(i.fir!=tar){
			tar=i.fir;
			For(j,0,n) cnt[j]=0;
			while(it!=c.end() && it->fir<i.fir) it++;
			while(it!=c.end() && it->fir==i.fir){
				cnt[it->sec]++;
				it++;
			}
		}
		For(j,i.sec,n) ans[j]+=cnt[j-i.sec];
	}
	For(i,1,n) cout<<ans[i]<<endl;
return 0;}
```

---

## 作者：enucai (赞：3)

## Preface

考场上被卡死了，没想到用双指针，wtcl。

## Analysis

观察数据范围 $n\le40$，直接想到 meet in the middle。 打起来也很方便。可以先处理出前 $\frac{n}{2}$ 个行动与后 $n-\frac{n}{2}$ 个行动分别能到达那些位置，用 map 或 哈希表 存储。最后枚举匹配。然而 map 很慢，哈希表不是被卡冲突就是被卡内存，恭喜你 TLE/MLE 了。

于是~~很容易~~想到用 双指针 来优化。先对于两半能到达的位置排个序，然后双指针扫过去，把位置相同的搞下来就好了，这样就免去了 map 带来的 $\log$，只需要在排序时加个 $\log$。于是通过了本题。

## Code

**Talk is cheap, show me the code.**

~~码风十分新奇。~~

```cpp
// And in that light, I find deliverance.
#define int long long
int n,l1,l2,gx,gy;
struct node{
	int x,y;
}a[45];
int ans[45],all[21];
vector<pair<pair<int,int>,int> > p1,p2,cur; 
signed main(){
	read(n,gx,gy);
	For(i,1,n) read(a[i].x,a[i].y);
	l1=n/2,l2=n-l1;
	p1.pb(mkp(mkp(0,0),0));
	For(i,1,l1){
		cur.clear();
		for(auto p:p1) cur.pb(mkp(mkp(p.fir.fir+a[i].x,p.fir.sec+a[i].y),p.sec+1));
		for(auto p:cur) p1.pb(p);
	}//左半边所有状态
	p2.pb(mkp(mkp(gx,gy),0));
	For(i,l1+1,n){
		cur.clear();
		for(auto p:p2) cur.pb(mkp(mkp(p.fir.fir-a[i].x,p.fir.sec-a[i].y),p.sec+1));
		for(auto p:cur) p2.pb(p);
	}//右半边所有状态
	sort(p1.begin(),p1.end());
	sort(p2.begin(),p2.end());
	pii lst=mkp(1e18,1e18);
	int pos=0;
	for(auto p:p1){
		if(p.fir!=lst){
			memset(all,0,sizeof(all));
			for(pos;pos<p2.size()&&p2[pos].fir<p.fir;pos++);
			for(pos;pos<p2.size()&&p2[pos].fir==p.fir;pos++) all[p2[pos].sec]++;//双指针
		}
		For(i,0,20) ans[i+p.sec]+=all[i];
		lst=p.fir;
	}
	For(i,1,n) printf("%lld\n",ans[i]);
}
```

---

## 作者：蒻蒟IOOI蒟蒻 (赞：3)

## Preface
题解好像都用的是双指针，这里提供一个用 ```unordered_map``` 的题解。

## Analysis 

数据范围 $n \le 40$，所以 $O(2^n)$ 的爆搜肯定过不了，可以用折半搜索 $O(2^\frac{n}2)$ 来优化。

我们把移动分为两部分，把前一半的行动和后一半的行动分开去搜。

很容易想到用 ```map``` 套 ```vector``` 来储存前一半的信息，然后在后一半的搜索中对前一半的信息进行处理。

但是 ```map``` 的时间复杂度是 $O(\log n)$，还是会超时。

我们可以用 ```unordered_map``` 来优化掉这个 $O(\log n)$。

但还是会超时，发现 ```vector``` 中有很多重复的信息，考虑用 ```unordered_map``` 套 ```unordered_map``` 来优化。

于是就愉快地通过了本题。

## Code


```cpp
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;
#define int long long
const int N = 50;
int n, m, ex, ey, ax[N], ay[N], ans[N];
struct node {
    int x, y;
    node() {}
    node(int _x, int _y) : x(_x), y(_y) {}
    bool operator <(const node &t) const &{
        if (x == t.x) return y < t.y;
        return x < t.x;
    }
    bool operator ==(const node &t) const &{
        return x == t.x && y == t.y;
    }
};
struct ha {
    size_t operator() (const node &t) const &{
        size_t h1 = hash<int>()(t.x * 1000000000ll + t.y);
        return h1;
    }
};
unordered_map<node, unordered_map<int, int>, ha> mp;
void dfs(int x, int y, int i, int step) {
    node t(x, y);
    mp[t][step]++;
    for (; i <= n >> 1; i++) {
        dfs(x + ax[i], y + ay[i], i + 1, step + 1);
    }
}
void dfs2(int x, int y, int i, int step) {
    node t(x, y);
    if (mp.count(t)) {
        unordered_map<int, int> nd = mp[t];
        for (unordered_map<int, int>::iterator it = nd.begin(); it != nd.end(); it++) ans[it -> first + step] += it -> second;
    }
    for (; i <= n; i++) {
        dfs2(x - ax[i], y - ay[i], i + 1, step + 1);
    }
}

signed main() {
    cin >> n >> ex >> ey;
    m = (n >> 1) + 1;
    for (int i = 1; i <= n; i++) cin >> ax[i] >> ay[i];
    dfs(0, 0, 1, 0);
    dfs2(ex, ey, m, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
    return 0;
}

```

---

## 作者：cff_0102 (赞：1)

> 正难则反，反难则正，正反都难，meet in the middle。

考虑 $N\le20$ 的部分分，可以直接暴力枚举所有 $2^N$ 种情况，可以通过。

注意到全部数据范围是 $N\le40$，那么从起点开始枚举前一半的选取情况，终点开始枚举后一半的选取情况即可（因为向量的加法满足交换律，只要选了不管放在哪最后到达的地方一定相同，所以才可以这样做）。

有一个技巧可以避免写太麻烦的 dfs：把当前能到达的所有结果存到一个 map 里面，枚举到一个新的向量时加到所有这些结果后面即可，当然时间复杂度仍然是指数级的，因为每枚举到一个新的时就会把当前 map 里的元素翻倍。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=45;
struct vec{
	int x,y;
	vec operator+(vec a){
		return {x+a.x,y+a.y};
	}
	vec operator-(vec a){
		return {x-a.x,y-a.y};
	}
	bool operator<(vec a)const{
		return make_pair(x,y)<make_pair(a.x,a.y);
	}
}v[N];
int ans[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	int xg,yg;cin>>xg>>yg;
	for(int i=1;i<=n;i++){
		cin>>v[i].x>>v[i].y;
	}
	map<pair<vec,int>,int>mp1,mp2;
	mp1[{{0,0},0}]=1;mp2[{{xg,yg},0}]=1;
	for(int i=1;i<=n/2;i++){
		auto mp=mp1;
		for(auto t:mp){
			auto nw=t.first;
			nw.first=nw.first+v[i];
			nw.second++;
			int x=t.second;
			mp1[nw]+=x;
		}
	}
	for(int i=n/2+1;i<=n;i++){
		auto mp=mp2;
		for(auto t:mp){
			auto nw=t.first;
			nw.first=nw.first-v[i];
			nw.second++;
			int x=t.second;
			mp2[nw]+=x;
		}
	}
	for(auto t:mp1){
		auto nw=t.first;int x=t.second;
		vec pos=nw.first;int nk=nw.second;
		for(int i=nk;i<=n;i++){
			int lk=i-nk;
			if(mp2.find({pos,lk})!=mp2.end()){
				ans[i]+=x*mp2[{pos,lk}];
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：1)

## Solution

看题先看数据 $N \le 40$，这应该是 $\mathcal O(2 \times N \times 2^{\frac{N}{2}})$ 折半搜索。

对于第一次搜索，每次加上编号从 $1$ 到 $[\dfrac{N}{2}]$ 的 正向量，对于第二次搜索，每次加上编号为 $N$ 到 $[\dfrac{N}{2}] + 1$ 的反向量。

考虑使用套三层的 `unordered_map` 存储第一次搜索的结果，第一层为 $x$ 坐标，第二层为 $y$ 坐标，第三层为 $c$，第一次搜索选了几个正向量，搜索完后将 $mp_{x,y,c} \gets mp_{x,y,c} + 1$，在第二次搜索完后将 $ans_{i} \gets ans_{i} + mp_{x,y,i-c}(c \le i \le k)$。

还有一个优化：在第二次搜索完后判断有没有这个状态才加，不然会 MLE。

## Code
```cpp
/* Python
rp = 0
while Ture:
    rp = rp + 1
*/
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const int kMaxN = (1 << 21);

ll n, sx, sy;
ll ans[kMaxN];
unordered_map<ll, unordered_map<ll, unordered_map<int, int>>> mp;
pii a[kMaxN];

void Dfs1(ll x, ll y, int dep, int c) {
  if (dep > n / 2) {
    mp[x][y][c]++;
    return;
  }
  Dfs1(x, y, dep + 1, c);
  Dfs1(x + a[dep].first, y + a[dep].second, dep + 1, c + 1);
}
void Dfs2(ll x, ll y, int dep, int c) {
  if (dep == n / 2) {
    for (int i = c; i <= n; i++) {
      if (mp.count(x) && mp[x].count(y) && mp[x][y].count(i - c)) {
        ans[i] += mp[x][y][i - c];
      }
    }
    return;
  }
  Dfs2(x - a[dep].first, y - a[dep].second, dep - 1, c + 1);
  Dfs2(x, y, dep - 1, c);
}

int main() {
  cin >> n >> sx >> sy;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  Dfs1(0, 0, 1, 0);
  Dfs2(sx, sy, n, 0);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
```

---

## 作者：huhangqi (赞：0)

看到 $1\le N\le 40$ 甚至部分分 $N\le 20$ 而且只有选和不选两种情况，这不是折半是什么？

那么直接考虑最板子的折半，前面一半从起点直接暴力搜索是否选择，得到最后的位置，另一半从终点往回走，最后统计是否有多少相等的数量即可。

但是分析一下时间复杂度，还是比较极限的，再加上如果你用 map 存储的话常数超级大，如果不卡卡常数最后可能就是压线通过的，卡常能力差一点可能会被某一些差一点的 OJ 卡。

那么考虑把 map 给优化掉。

我们直接用 vector 来存储，然后直接排序，在末尾统计时直接使用一个指针查找相同的数量，每次都只会遍历一次，时间复杂度直接优化掉了一个 $\log$ 以及超级巨大的常数。

需要注意的是判断是否有相同的情况。

当然这道题目还可以优化，可以试着直接将几个选择数量不同的直接放在一起处理，不过整体意义也不大，所以就没有写。

下面一个是 map 的，上面一个是 vector 的，可见差距确实非常大，事实证明能不要随便用 map，当然也不排除是我的 map 写得太差了。

![](https://cdn.luogu.com.cn/upload/image_hosting/qyre9z0h.png)

vector 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[45],y[45],ex,ey,p[45];
long long ans[45];
vector<pair<int,int>> e[45],e2[45];
void dfs(int p,int z,int sum,int xx,int yy,bool f){
	if(f)e[sum].push_back({xx,yy});
	if(p>z)return;
	dfs(p+1,z,sum,xx,yy,0);
	dfs(p+1,z,sum+1,xx+x[p],yy+y[p],1);
}
void dfs2(int p,int z,int sum,int xx,int yy,bool f){
	if(f)e2[sum].push_back({xx,yy});
	if(p>z)return;
	dfs2(p+1,z,sum,xx,yy,0);
	dfs2(p+1,z,sum+1,xx-x[p],yy-y[p],1);
}
bool cmp(pair<int,int> x,pair<int,int> y){
	return x<y;
}
signed main(){
	cin>>n;
	cin>>ex>>ey;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	dfs(1,(n+1)/2,0,0,0,1);
	dfs2((n+1)/2+1,n,0,ex,ey,1);
	for(int i=0;i<=(n+1)/2;i++)sort(e[i].begin(),e[i].end());
	for(int i=0;i<=(n+1)/2;i++)sort(e2[i].begin(),e2[i].end());
	for(int i=0;i<=(n+1)/2;i++){
		for(int j=0;j<=(n+1)/2;j++)p[j]=0;
		for(int o=0;o<e[i].size();o++){
			pair<int,int> k=e[i][o];
			int sum=1;
			while(o+1<e[i].size()&&e[i][o+1]==k)o++,sum++;
			for(int j=0;j<=(n+1)/2;j++){
				while(p[j]<e2[j].size()&&e2[j][p[j]]<k)p[j]++;
				while(p[j]<e2[j].size()&&e2[j][p[j]]==k)ans[j+i]+=1ll*sum,p[j]++;
			}	
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}

``````

---

## 作者：_Day_Tao_ (赞：0)

这个题看上去就很 `meet in the middle` 吧。考虑将所有的步骤均分为两份，然后对每一份进行枚举，每个能拼成的向量的总方案数是 $2^{\frac{n}{2}}$ 种。接着考虑将两块内的每种向量相加得到最终的答案点，这样就可以想到用 `map` 存下某一块的答案，然后用另一块去查询累加答案。枚举 $k$ 与枚举每一种 $k$ 的和的复杂度共为 $O(n^2)$，再加上用 `map` 存，总复杂度就是 $O(2^{\frac{n}{2}}\times n^2\log 2^{\frac{n}{2}})$，过不去。然后可以想到用哈希，具体地，就是将每个 $x$ 乘上一个数再加上 $y$，这样复杂度就变为了 $O(n^{\frac{n}{2}})$ 再加哈希的常数。虽然最终的用时比较唐，但是至少能过嘛（

**Code:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pll pair<long long, long long>
#define ls root << 1
#define rs root << 1 | 1
#define ull unsigned long long
// #define int long long
#define mid ((l+r)>>1)
inline long long read(){
	long long x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int base = 998244353;
struct Day_Tao
{
	long long x,y;
}a[41];
unordered_map<ull,int>res[41];
long long n,ans[41],xx,yy;
void dfs(long long x,long long y,int i,int lim,int cnt,bool fl)
{
	if(fl) // 在上一个选了的情况下才能进行答案的累加，不然会重复 
	{
		if(lim==n/2) res[cnt][1ull*x*base+y]++;
		else
		{
			for(int j=0;j+cnt<=n;j++)
				if(res[j].find(1ull*xx*base-1ull*x*base+yy-y)!=res[j].end()) // 记得这边判一下，不然会默认新开了个数字， 
					ans[j+cnt]+=res[j][1ull*xx*base-1ull*x*base+yy-y]; // 徒增复杂度（而且不加好像过不了
		}
		
	}
	if(i==lim+1) return ;
	dfs(x,y,i+1,lim,cnt,0),dfs(x+a[i].x,y+a[i].y,i+1,lim,cnt+1,1);
	return ;
}
signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	n=read();
	xx=read(),yy=read();
	for(int i=1;i<=n;i++) a[i]={read(),read()};
	dfs(0,0,1,n/2,0,1),dfs(0,0,n/2+1,n,0,1); // 两个 dfs 都写到一起了，所以要多加几维 
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	system("pause");
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 1 - 算法讲解

考虑二进制枚举，对于每次操作都可以选或不选，时间复杂度是 $O(2 ^ n)$。于是我们考虑两个 dfs，一个从 $(0,0)$ 开始搜，另外一个从 $(x_g,y_g)$ 开始搜，在中间汇合，即 meet-in-the-middle。

[双倍经验](https://www.luogu.com.cn/article/kjf3z0uv)。两者非常的相似。这道题我们也采取同样的存储方式，使用 map。从前往后搜时进行记录，从后往前搜时寻找记录并加到答案里。对于 map 的 $O(\log n)$，我们可以使用 unordered_map 优化掉。于是时间复杂度就降为 $O(2^\frac{n}{2})$ 啦。

# Part 2 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, s, t, dx[50], dy[50], ans[50];

struct hsh {
	size_t operator() (const pair<ll, ll> &p) const & {
		size_t h = hash<ll> () (p.first * 1e9 + p.second);
		return h;
	}
};

unordered_map<pair<ll, ll>, unordered_map<ll, ll>, hsh> m;

void dfs1(ll x, ll y, ll p, ll k) {
	m[{x, y}][k]++;
	for (ll i = p; i <= n / 2; i++) {
		dfs1(x + dx[i], y + dy[i], i + 1, k + 1);
	}
}

void dfs2(ll x, ll y, ll p, ll k) {
	if (m.count({x, y})) {
		unordered_map<ll, ll> mp = m[{x, y}];
		for (auto it = mp.begin(); it != mp.end(); it++) {
			ans[it -> first + k] += it -> second;
		}
	}
	for (ll i = p; i <= n; i++) {
		dfs2(x - dx[i], y - dy[i], i + 1, k + 1);
	}
}

int main() {

	scanf("%lld %lld %lld", &n, &s, &t);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld %lld", &dx[i], &dy[i]);
	}
	dfs1(0, 0, 1, 0);
	dfs2(s, t, n / 2 + 1, 0);
	for (ll i = 1; i <= n; i++) {
		printf("%lld\n", ans[i]);
	}

	return 0;
}

```

---

## 作者：lg_zhou (赞：0)

这道题我被卡时限卡了亿点点。

$2 - 4$ 组数据，$n < 20$ 的范围，赤裸裸的爆搜，从起点 dfs , 到终点就将相应的步数答案加一即可。

***

后面的数据 $n<40$ , $2^{40}$ 显然是过不了的，很容易想到折半搜索，可以从起点先往后搜索，把到的每个点放进哈希表里。再从终点往前搜，到达每个点的同时枚举之前到达这里的步数，并累积答案。

注意哈希表不可以直接用 ```map```  实现，复杂度会爆掉，可以用 ```unordered_map``` 或手写哈希表。

一些奇技淫巧：
* 构造哈希函数的时候可以反复试试不同的，测测时间
* 从起点往后搜的个数可以比从终点往前多，因为从终点搜的时候还要枚举累计答案。

代码就不放了，思路明白后实现没有什么思维，就是爆搜。~~主要是因为时间太长了没脸放~~。


---

