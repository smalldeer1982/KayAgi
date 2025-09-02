# 题目信息

# Unfair Poll

## 题目描述

On the Literature lesson Sergei noticed an awful injustice, it seems that some students are asked more often than others.

Seating in the class looks like a rectangle, where $ n $ rows with $ m $ pupils in each.

The teacher asks pupils in the following order: at first, she asks all pupils from the first row in the order of their seating, then she continues to ask pupils from the next row. If the teacher asked the last row, then the direction of the poll changes, it means that she asks the previous row. The order of asking the rows looks as follows: the $ 1 $ -st row, the $ 2 $ -nd row, $ ... $ , the $ n-1 $ -st row, the $ n $ -th row, the $ n-1 $ -st row, $ ... $ , the $ 2 $ -nd row, the $ 1 $ -st row, the $ 2 $ -nd row, $ ... $

The order of asking of pupils on the same row is always the same: the $ 1 $ -st pupil, the $ 2 $ -nd pupil, $ ... $ , the $ m $ -th pupil.

During the lesson the teacher managed to ask exactly $ k $ questions from pupils in order described above. Sergei seats on the $ x $ -th row, on the $ y $ -th place in the row. Sergei decided to prove to the teacher that pupils are asked irregularly, help him count three values:

1. the maximum number of questions a particular pupil is asked,
2. the minimum number of questions a particular pupil is asked,
3. how many times the teacher asked Sergei.

If there is only one row in the class, then the teacher always asks children from this row.

## 说明/提示

The order of asking pupils in the first test:

1. the pupil from the first row who seats at the first table, it means it is Sergei;
2. the pupil from the first row who seats at the second table;
3. the pupil from the first row who seats at the third table;
4. the pupil from the first row who seats at the first table, it means it is Sergei;
5. the pupil from the first row who seats at the second table;
6. the pupil from the first row who seats at the third table;
7. the pupil from the first row who seats at the first table, it means it is Sergei;
8. the pupil from the first row who seats at the second table;

The order of asking pupils in the second test:

1. the pupil from the first row who seats at the first table;
2. the pupil from the first row who seats at the second table;
3. the pupil from the second row who seats at the first table;
4. the pupil from the second row who seats at the second table;
5. the pupil from the third row who seats at the first table;
6. the pupil from the third row who seats at the second table;
7. the pupil from the fourth row who seats at the first table;
8. the pupil from the fourth row who seats at the second table, it means it is Sergei;
9. the pupil from the third row who seats at the first table;

## 样例 #1

### 输入

```
1 3 8 1 1
```

### 输出

```
3 2 3```

## 样例 #2

### 输入

```
4 2 9 4 2
```

### 输出

```
2 1 1```

## 样例 #3

### 输入

```
5 5 25 4 3
```

### 输出

```
1 1 1```

## 样例 #4

### 输入

```
100 100 1000000000000000000 100 100
```

### 输出

```
101010101010101 50505050505051 50505050505051```

# AI分析结果

### 题目内容
# 不公平的提问

## 题目描述
在文学课上，谢尔盖注意到了一种极其不公平的现象，似乎有些学生被提问的频率比其他学生更高。
教室里学生的座位呈矩形排列，有 $n$ 行，每行有 $m$ 个学生。
老师按以下顺序提问学生：首先，她按座位顺序依次提问第一行的所有学生，然后继续提问下一行的学生。如果老师问到了最后一行，提问方向就会改变，即她会提问上一行的学生。提问行的顺序如下：第1行，第2行，...，第 $n - 1$ 行，第 $n$ 行，第 $n - 1$ 行，...，第2行，第1行，第2行，...
在同一行中提问学生的顺序始终不变：第1个学生，第2个学生，...，第 $m$ 个学生。
在这节课上，老师按照上述顺序恰好提问了 $k$ 个问题。谢尔盖坐在第 $x$ 行，该行的第 $y$ 个位置。谢尔盖决定向老师证明学生被提问的频率不一致，请帮他计算三个值：
1. 某个学生被提问的最大次数。
2. 某个学生被提问的最小次数。
3. 老师提问谢尔盖的次数。
如果教室里只有一行学生，那么老师总是从这一行提问学生。

## 说明/提示
第一个测试用例中提问学生的顺序：
1. 第一行坐在第一张桌子的学生，也就是谢尔盖；
2. 第一行坐在第二张桌子的学生；
3. 第一行坐在第三张桌子的学生；
4. 第一行坐在第一张桌子的学生，也就是谢尔盖；
5. 第一行坐在第二张桌子的学生；
6. 第一行坐在第三张桌子的学生；
7. 第一行坐在第一张桌子的学生，也就是谢尔盖；
8. 第一行坐在第二张桌子的学生；

第二个测试用例中提问学生的顺序：
1. 第一行坐在第一张桌子的学生；
2. 第一行坐在第二张桌子的学生；
3. 第二行坐在第一张桌子的学生；
4. 第二行坐在第二张桌子的学生；
5. 第三行坐在第一张桌子的学生；
6. 第三行坐在第二张桌子的学生；
7. 第四行坐在第一张桌子的学生；
8. 第四行坐在第二张桌子的学生，也就是谢尔盖；
9. 第三行坐在第一张桌子的学生；

## 样例 #1
### 输入
```
1 3 8 1 1
```
### 输出
```
3 2 3```

## 样例 #2
### 输入
```
4 2 9 4 2
```
### 输出
```
2 1 1```

## 样例 #3
### 输入
```
5 5 25 4 3
```
### 输出
```
1 1 1```

## 样例 #4
### 输入
```
100 100 1000000000000000000 100 100
```
### 输出
```
101010101010101 50505050505051 50505050505051```

### 算法分类
数学

### 综合分析与结论
这三道题解思路基本一致，均先分析出老师提问顺序的周期性规律，一轮提问中第1行和第n行的学生被问1次，其余行学生被问2次，一轮提问的问题数为 $(2n - 2) \times m$（$n = 1$ 时特判为 $m$） 。通过总问题数 $k$ 计算提问轮数和最后一轮剩余问题数，再据此计算每个学生的被问次数，从而得出最大、最小被问次数以及指定学生的被问次数。
不同点在于实现细节和代码风格，如变量命名、输入方式、求最值方式等。

### 所选的题解
- **作者：Cloud_Umbrella（4星）**
    - **关键亮点**：思路清晰，代码简洁明了，注释详细，对关键步骤和变量含义有较好说明。
    - **重点代码**：
```c++
int main(){
    scanf("%d%d%lld%d%d",&n,&m,&k,&x,&y);
    ans2=k,tot=max(2*n-2,1)*m;
    s=k/tot,t=k%tot;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(i==1 || i==n) a[i][j]=s;
            else a[i][j]=s<<1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m && t;j++,t--)
            a[i][j]++;
    for(int i=n-1;i>1;i--)
        for(int j=1;j<=m && t;j++,t--)
            a[i][j]++;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            ans1=max(a[i][j],ans1);
            ans2=min(a[i][j],ans2);
        }
    printf("%lld %lld %lld",ans1,ans2,a[x][y]);
    return 0;
}
```
    - **核心实现思想**：先计算总轮数 $s$ 和最后一轮剩余问题数 $t$ ，初始化每个学生的被问次数，再根据最后一轮剩余问题数更新学生被问次数，最后遍历所有学生找到最大、最小被问次数以及指定学生的被问次数并输出。
- **作者：zhengenzhe（4星）**
    - **关键亮点**：代码模块化，将不同功能封装成函数，结构清晰，还包含快速读入模板。
    - **重点代码**：
```c++
void pretreatment(){
    if(2*n-2>1){
        cnt=(2*n-2)*m;
    }else{
        cnt=m;
    }
    lunshu=k/cnt;
    last_student=k%cnt;
}
void work1(){
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m&&last_student>=1;j++,last_student--){
            a[i][j]++;
        }
    }  
}
void work2(){
    for(ll i=n-1;i>=2;i--){
        for(ll j=1;j<=m&&last_student>=1;j++,last_student--){
            a[i][j]++;
        }
    }
}
void find(){
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            if(a[i][j]>ans1){
                ans1=a[i][j];
            }
            if(a[i][j]<ans2){
                ans2=a[i][j];
            }
        }
    }
}
int main(){
    read(n);
    read(m);
    read(k);
    read(x);
    read(y);
    pretreatment();
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            if(i==1||i==n){
                a[i][j]=lunshu;
                continue;
            }
            a[i][j]=lunshu*2;
            continue;
        }
    }
    work1();
    work2();
    find();
    cout<<ans1<<" "<<ans2<<" "<<a[x][y]<<'\n';
    return 0;
}
```
    - **核心实现思想**：通过 `pretreatment` 函数计算轮数和最后一位同学，`work1` 和 `work2` 函数分别按顺序更新学生被问次数，`find` 函数寻找最大最小值，最后在 `main` 函数整合并输出结果。
- **作者：_Kimi_（4星）**
    - **关键亮点**：使用 `max_element` 和 `min_element` 求最值，代码简洁高效，对 `n = 1` 的情况单独处理逻辑清晰。
    - **重点代码**：
```cpp
signed main(){
    input();
    if(n == 1){
        vector<int> A(m);
        for(int i = 0; i < m; i++){
            if(i < (k % m)) A[i]++;
            A[i] += (k / m);
        }
        int maxx = -inf, minn = inf;
        maxx = max(maxx, *max_element(A.begin(), A.end()));
        minn = min(minn, *min_element(A.begin(), A.end()));
        cout << maxx << ' ' << minn << ' ' << A[y] << endl;
    }else{
        int cnt = (n * 2 - 2) * m;
        int pos = (k / cnt);
        int maxx = -inf, minn = inf;
        k %= cnt;
        vector<vector<int>> A(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == n - 1 || i == 0) A[i][j] = pos;
                else A[i][j] = pos * 2;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (k) k--, A[i][j]++;
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                if (k) k--, A[i][j]++;
            }
        }
        for (int i = 0; i < n; i++) {
            maxx = max(maxx, *max_element(A[i].begin(), A[i].end()));
            minn = min(minn, *min_element(A[i].begin(), A[i].end()));
        }
        cout << maxx << ' ' << minn << ' ' << A[x][y] << endl;
    }
    return 0;
}
```
    - **核心实现思想**：`n = 1` 时单独处理，计算每个学生被问次数并求最值输出。`n > 1` 时，计算周期、轮数和剩余问题数，初始化学生被问次数，按顺序更新，最后求最值并输出指定学生被问次数。

### 最优关键思路或技巧
1. **周期性分析**：准确找出老师提问顺序的周期性规律，以此为基础计算轮数和剩余问题数，简化问题求解。
2. **特判处理**：对 `n = 1` 的特殊情况进行单独处理，保证程序的完整性和正确性。
3. **利用标准库函数**：如 `_Kimi_` 的题解中利用 `max_element` 和 `min_element` 求最值，简化代码实现。

### 拓展
同类型题可关注具有周期性规律的计数问题，类似算法套路是先分析出规律，确定周期，再根据总次数计算周期数和剩余部分，进而求解问题。

### 洛谷题目推荐
1. **P1088 [NOIP2004 普及组] 火星人**：涉及到对排列规律的分析和计数，与本题分析规律求解的思路类似。
2. **P1145 中缀表达式**：通过分析表达式的运算顺序规律来解决问题，和本题找提问顺序规律有相似之处。
3. **P1908 逆序对**：通过分析序列元素间的顺序关系来计数，与本题分析座位顺序和提问次数关系类似。 

---
处理用时：92.26秒