package com.gamm.thirdlogindemo;

import android.util.Log;

import com.gamm.thirdlogin.util.GammMd5;

import java.util.Comparator;
import java.util.Map;
import java.util.TreeMap;

/**
 * 仅demo中使用
 *
 * Created by panda on 2017/11/12.
 */
public class Md5Demo {
    public static String md5BySort(Map<String, Object> map) {
        Map<String, String> sortedMap = new TreeMap<String, String>(
                new Comparator<String>() {
                    public int compare(String obj1, String obj2) {
                        return obj2.compareTo(obj1);
                    }
                });
        for (Map.Entry<String, Object> entry : map.entrySet()) {
            sortedMap.put(entry.getKey(), String.valueOf(entry.getValue()));
        }

        StringBuffer str = new StringBuffer();
        for (Map.Entry<String, String> entry : sortedMap.entrySet()) {
            str.append(entry.getKey()).append("=").append(entry.getValue()).append("&");
        }
        String str2 = str.toString();
        if (str2.length() > 1) {
            str2 = str.substring(0, str2.length() - 1);
        }

        Log.e("111", "first sign str: " + str2);

        String s = GammMd5.md5(str2);
        Log.e("111", "second sign str: " + s + "&app_key=" + App.appKey);
        return GammMd5.md5(s + "&app_key=" + App.appKey);
    }
}
