void divide_function(int * dividend, int dividend_l, int * divisor, int divisor_l, int * result, int * result_l){
    /* divide arr by val, return result in result and r */
    int tmp, i_dividend, i_result = 0, divisor_val = b_base_to_decimal(divisor, divisor_l);
    if (less_than(dividend, dividend_l, divisor, divisor_l)){
        result[0] = 0;
        *result_l = 1;
        return;
    }
    i_dividend = divisor_l - 1;
    *result_l = 0;
    tmp = b_base_to_decimal(dividend, divisor_l);
    while(i_dividend < dividend_l){
        result[i_result] = tmp / divisor_val;
        i_result++;
        tmp = tmp % divisor_val;
        i_dividend++;
        tmp = tmp * base + dividend[i_dividend];
    }
    *result_l = i_result;
}

int less_than(int *arr1, int arr1_l, int * arr2, int arr2_l){
    if(arr1_l < arr2_l)
        return 1;
    if(arr1_l > arr2_l)
        return 0;
    for(int i = 0; i < arr1_l; i++){
        if(arr1[i] < arr2[i]){
            return 1;
        }
        else if(arr1[i] > arr2[i]){
            return 0;
        }
    }
    return 0;
}

int b_base_to_decimal(int *arr, int arr_l){
    int result = 0, e = arr_l - 1; 
    for(int i = 0; i < arr_l; i++){
        result += arr[i] * (int)pow(base, e);
        e--;
    }
    return result;
}

void multiply_function(int * factor, int factor_l, int val, int * result, int * result_l){
    int r = 0, tmp_result[factor_l + 1];
    int i_tmp_result = 0, t;
    for(int i = factor_l - 1; i >= 0; i--){
        t = val * factor[i] + r;
        tmp_result[i_tmp_result] = t % base;
        r = t / base;
        i_tmp_result++;
    }
    for(int i = 0; i < i_tmp_result; i++){
        result[i] = tmp_result[i_tmp_result - i - 1];
    }
    *result_l = i_tmp_result;
}

void multiply_function(int * factor1, int factor1_l, int * factor2, int factor2_l, int * result, int * result_l){
    int num_zeros = 0, sum[factor1_l + factor2_l], sum_l = 0, tmp[factor1_l + factor2_l], tmp_l = 0;
    for(int i = factor2_l - 1; i >= 0; i--){
        multiply_function(factor1, factor1_l, factor2[i], tmp, &tmp_l);
        for(int j = 0; j < num_zeros; j++){
            tmp[tmp_l] = 0; 
            tmp_l++;
        }
        add_function(sum, sum_l, tmp, tmp_l, sum, &sum_l);
        num_zeros++;
    }
    *result_l = sum_l;
    for(int i = 0; i < sum_l; i++){
        result[i] = sum[i];
    }
}

void add_function(int * addend1, int addend1_l, int * addend2, int addend2_l, int * result, int * result_l){
    int max = addend1_l < addend2_l?addend2_l:addend1_l; 
    int r = 0, tmp_sum, i1 = addend1_l - 1, i2 = addend2_l - 1, rev_result[max + 1]; 
    int i = 0;
    while(i1 >= 0 && i2 >= 0){
        tmp_sum = addend1[i1] + addend2[i2] + r;
        rev_result[i] = tmp_sum % base;
        r = tmp_sum / base;
        i++;
        i1--;
        i2--;
    }
    if(i1 >= 0){
        while(i1 >= 0){
            tmp_sum = addend1[i1] + r;
            rev_result[i] = tmp_sum % base;
            r = tmp_sum / base;
            i1--;
            i++;
        }
    }
    if(i2 >= 0){
        while(i2 >= 0){
            tmp_sum = addend2[i2] + r;
            rev_result[i] = tmp_sum % base;
            r = tmp_sum / base;
            i2--;
            i++;
        }
    }
    for(int k = 0; k < i; k++){
        result[k] = rev_result[i - 1 - k];
    }
    *result_l = i;
}
