# 排序

## 插入排序

### 直接插入排序
```cpp
void InsertSort(Sqlist &L)
{
    int i;
    int j;
    for (i = 2; i <= L.length; i++){
        if (L.r[i] < L.r[i-1])
        {
            L.r[0] = L.r[i];
            for (j = i-1; L.r[0] < L.r[j]; j--)
            {
                L.r[j+1] = L.r[j];
            }
            L.r[j+1] = L.r[0];
        }
    }
}
```

### 希尔排序
希尔排序是一种不稳定的排序

## 交换排序

### 冒泡排序

### 快速排序