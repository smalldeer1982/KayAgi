# 题目信息

# Blue-Red Permutation

## 题目描述

有 $n$ 个数，每个数是红色或蓝色。你可以进行无限次操作（也可以 $0$ 次），每次操作你可以：

1. 把一个蓝色的数 $-1$ 。
2. 把一个红色的数 $+1$ 。

问是否能将这 $n$ 个数变成 $1$ 到 $n$ 的排列，是就输出 `YES` ，否则 `NO` 。

## 说明/提示

$1 \le T \le 10^4$ ，$1 \le n \le 2 \times 10^5$ ， $-10^9 \le a_i \le 10^9$ ，$\sum n \le 2 \times 10^5$ 。

## 样例 #1

### 输入

```
8
4
1 2 5 2
BRBR
2
1 1
BB
5
3 1 4 2 5
RBRRB
5
3 1 3 1 3
RBRRB
5
5 1 5 1 5
RBRRB
4
2 2 2 2
BRBR
2
1 -2
BR
4
-2 -1 4 0
RRRR```

### 输出

```
YES
NO
YES
YES
NO
YES
YES
YES```

# AI分析结果

### 题目翻译
# 蓝红排列

## 题目描述

有 $n$ 个数，每个数是红色或蓝色。你可以进行无限次操作（也可以 $0$ 次），每次操作你可以：

1. 把一个蓝色的数 $-1$ 。
2. 把一个红色的数 $+1$ 。

问是否能将这 $n$ 个数变成 $1$ 到 $n$ 的排列，是就输出 `YES` ，否则 `NO` 。

## 说明/提示

$1 \le T \le 10^4$ ，$1 \le n \le 2 \times 10^5$ ， $-10^9 \le a_i \le 10^9$ ，$\sum n \le 2 \times 10^5$ 。

## 样例 #1

### 输入

```
8
4
1 2 5 2
BRBR
2
1 1
BB
5
3 1 4 2 5
RBRRB
5
3 1 3 1 3
RBRRB
5
5 1 5 1 5
RBRRB
4
2 2 2 2
BRBR
2
1 -2
BR
4
-2 -1 4 0
RRRR```

### 输出

```
YES
NO
YES
YES
NO
YES
YES
YES```

### 算法分类
贪心

### 综合分析与结论
这道题的核心思路是通过贪心策略，将蓝色和红色的数分别排序，然后检查是否能够通过操作将它们转化为1到n的排列。蓝色数只能减少，红色数只能增加，因此蓝色数需要尽可能小，红色数需要尽可能大。通过排序和简单的条件检查，可以高效地判断是否能够满足条件。

### 所选题解
1. **作者：SxEe (赞：7)**  
   - **星级：4星**  
   - **关键亮点**：思路清晰，代码简洁，通过将红色和蓝色的数分别排序，并检查是否满足条件，实现了高效的贪心策略。
   - **代码核心思想**：
     ```cpp
     sort(red+1,red+rl+1); 
     sort(blue+1,blue+bl+1);
     bool o=true;
     for(int i=1;i<=bl;i++){
         if(blue[i]<i)o=false;
     }
     for(int i=rl;i>=1;i--){
         if(red[i]>n-(rl-i))o=false;
     }
     if(o)cout<<"YES"<<endl;
     else cout<<"NO"<<endl;
     ```

2. **作者：Ninelife_Cat (赞：4)**  
   - **星级：4星**  
   - **关键亮点**：通过将红色和蓝色的数分别排序，并检查是否满足条件，思路清晰，代码简洁。
   - **代码核心思想**：
     ```cpp
     sort(R.begin(),R.end(),Cmp);
     sort(B.begin(),B.end());
     for(ri int i=0;i<R.size();++i)
         if(R[i]>n-i) {cout<<"NO\n";goto end;}
     for(ri int i=0;i<B.size();++i)
         if(B[i]<i+1) {cout<<"NO\n";goto end;}
     cout<<"YES\n";end:;
     ```

3. **作者：引领天下 (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：通过优先使用蓝色数的策略，避免了红色数无法满足条件的情况，思路独特且有效。
   - **代码核心思想**：
     ```cpp
     auto x=(dc.size()?*dc.begin():0),y=(ic.size()?*ic.begin():n+1);
     if(x<i&&y>i){cout<<"NO\n";flag=0;continue;}
     if(x>=i)dc.erase(dc.begin());
     else ic.erase(ic.begin());
     ```

### 最优关键思路或技巧
1. **贪心策略**：将蓝色和红色的数分别排序，蓝色数从小到大，红色数从大到小，然后检查是否满足条件。
2. **优先使用蓝色数**：在满足条件的情况下，优先使用蓝色数，避免红色数无法满足条件的情况。

### 可拓展之处
类似的问题可以通过贪心策略来解决，尤其是在需要将一组数通过有限的操作转化为特定排列的情况下。例如，可以通过类似的思路解决其他类型的排列问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：31.72秒