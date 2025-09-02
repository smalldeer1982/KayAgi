# 题目信息

# Cutting

## 题目描述

有一个整数序列，其偶数和奇数的数量相同。给定有限的预算，您需要尽可能多地进行切割，使每个结果段具有相同数量的奇数和偶数。

“切割”操作将一个序列分成 $2$ 个连续的段。您可以将每次“切割”看作是序列中两个相邻元素之间的中断。所以在切割之后每个元素恰好属于一个片段。

举个例子，$[4,1,2,3,4,5,4,4,5,5]\to$ 两次“切割”操作 $\to[4,1|2,3,4,5|4,4,5,5]$。在每个切割后的段上，偶数元素的个数应该等于奇数元素的个数。

在元素 $x$ 和元素 $y$ 之间进行一次“切割”操作的价值为 $|x-y|$ 元。请问，在 $B$ 元内，最多可以切割几次？

## 样例 #1

### 输入

```
6 4
1 2 5 10 15 20
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 10
1 3 2 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 100
1 2 3 4 5 6
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写
有一个整数序列，其偶数和奇数的数量相同。给定有限的预算，您需要尽可能多地进行切割，使每个结果段具有相同数量的奇数和偶数。

“切割”操作将一个序列分成 $2$ 个连续的段。您可以将每次“切割”看作是序列中两个相邻元素之间的中断。所以在切割之后每个元素恰好属于一个片段。

举个例子，$[4,1,2,3,4,5,4,4,5,5]\to$ 两次“切割”操作 $\to[4,1|2,3,4,5|4,4,5,5]$。在每个切割后的段上，偶数元素的个数应该等于奇数元素的个数。

在元素 $x$ 和元素 $y$ 之间进行一次“切割”操作的价值为 $|x-y|$ 元。请问，在 $B$ 元内，最多可以切割几次？

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心算法，尽可能多地进行切割，且每次切割的代价最小。多个题解都采用了类似的思路：首先预处理所有可以切割的点，并计算每次切割的代价，然后按照代价从小到大排序，依次进行切割，直到预算用完。

### 所选题解
#### 1. 作者：quanjun (赞：1)
- **星级**：4星
- **关键亮点**：使用贪心算法，通过排序或优先队列选择最小代价的切割点，思路清晰，代码简洁。
- **核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  const int maxn = 110;

  int n, B, cnt, a[maxn], cc[maxn];
  vector<int> vec;

  int main() {
      cin >> n >> B;
      for (int i = 1; i <= n; i ++) {
          cin >> a[i];
          cc[i] = cc[i-1] + (a[i] % 2 ? 1 : -1);
      }
      for (int i = 1; i < n; i ++) if (!cc[i]) vec.push_back(abs(a[i+1]-a[i]));
      sort(vec.begin(), vec.end());
      for (vector<int>::iterator it = vec.begin(); it != vec.end(); it ++) {
          if (*it > B) break;
          B -= *it;
          cnt ++;
      }
      cout << cnt << endl;
      return 0;
  }
  ```

#### 2. 作者：_frog (赞：0)
- **星级**：4星
- **关键亮点**：详细分析了切割的顺序不影响结果，使用贪心算法从小到大选择切割点，代码实现清晰。
- **核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  typedef long long ll;

  inline ll read() {
      ll nov = 1, dat = 0;
      char c = getchar();
      while (c < '0' || c > '9') {
          if (c == '-')
              nov = -1;
          c = getchar();
      }
      while (c >= '0' && c <= '9') {
          dat = (dat << 3) + (dat << 1) + (c & 15);
          c = getchar();
      }
      return dat * nov;
  }

  void write(ll x) {
      if (x < 0) {
          putchar('-');
          x = -x;
      }
      if (x < 10) {
          putchar(x + '0');
      } else {
          write(x / 10);
          putchar(x % 10 + '0');
      }
  }
  ll a[110], now, ans, n, b;//now 表示目前奇数比偶数多多少个
  vector<ll>cutting;//用 vector 保存“切割”代价

  int main() {
      //1.输入
      n = read(), b = read();
      for (ll i = 1; i <= n; i++) {
          a[i] = read();
      }
      //2.预处理
      for (ll i = 1; i < n; i++) { //a[n] 后面无法“切割”
          if (a[i] % 2 == 1) { //a[i] 是奇数
              now++;
          } else { //a[i] 是偶数
              now--;
          }
          if (now == 0) { //奇数、偶数数量相等
              cutting.push_back(llabs(a[i + 1] - a[i]));//可以“切割”
          }
      }
      sort(cutting.begin(), cutting.end()); //根据“切割”代价从小到大排序
      //vector.end() 迭代器指向最后一个元素的下一位
      //3.模拟“切割”
      for (ll i = 0; i < cutting.size(); i++) {
          if (b >= cutting[i]) { //还可以进行“切割”
              b -= cutting[i];
              ans++;
          } else { //预算不足
              break;
          }
      }
      //4.输出
      write(ans);
      return 0;
  }
  ```

#### 3. 作者：Dream__Sky (赞：0)
- **星级**：4星
- **关键亮点**：使用贪心算法，预处理所有可以切割的点，并按代价排序，代码简洁明了。
- **核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  int n,k,a[100001],b[100001],cnt,daan;
  int main()
  {
      cin>>n>>k;
      for(int i=1;i<=n;i++) cin>>a[i];
      
      int sum1=0,sum2=0;
      for(int i=1;i<n;i++)//坑点，最后一个点不能分割
      {
          if(a[i]%2==1) sum1++;
          else sum2++;
          if(sum2==sum1) b[++cnt]=abs(a[i+1]-a[i]);//把所有可以的点的代价存下来
       } 
       
       sort(b+1,b+1+cnt);//贪心
       
       for(int i=1;i<=cnt;i++)
       {
          if(k>=b[i]) daan++,k-=b[i];
          else break;
       }
       cout<<daan;
      return 0;
  }
  ```

### 最优关键思路或技巧
1. **预处理所有可以切割的点**：通过遍历序列，记录每个位置之前奇数和偶数的数量，判断是否可以进行切割。
2. **贪心选择最小代价的切割点**：将所有可以切割的点按照代价从小到大排序，依次选择最小的代价进行切割，直到预算用完。

### 可拓展之处
类似的问题可以扩展到其他类型的切割或分割问题，例如在满足某些条件的情况下，尽可能多地进行分割。贪心算法在处理这类问题时通常非常有效。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：46.74秒