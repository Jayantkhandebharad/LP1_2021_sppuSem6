//package rpc;
// package com.company;

import java.io.*;
import java.net.*;
import java.lang.*;

public class server {
    public static void main(String[] args) throws Exception {
        ServerSocket sersock = new ServerSocket(6600); // i t create socket at server side, and allocate port,
        System.out.println("Server ready");
        Socket sock = sersock.accept(); // it accepting the call...whether its add,sub,multiply,division
        OutputStream ostream = sock.getOutputStream();
        PrintWriter pwrite = new PrintWriter(ostream, true);
        InputStream istream = sock.getInputStream();
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));
        String fun;
        int a, b, c;

        fun = receiveRead.readLine();
        if (fun != null)
            System.out.println("Operation : " + fun);
        a = Integer.parseInt(receiveRead.readLine());
        System.out.println("Parameter 1 : " + a);
        b = Integer.parseInt(receiveRead.readLine());
        System.out.println("Parameter 2 : " + b);
        if (fun.compareTo("add") == 0) {
            c = a + b;
            System.out.println("Addition = " + c);
            pwrite.println("Addition = " + c);
        }
        if (fun.compareTo("sub") == 0) {
            c = a - b;
            System.out.println("Subtraction = " + c);
            pwrite.println("Subtraction = " + c);
        }
        if (fun.compareTo("mul") == 0) {
            c = a * b;
            System.out.println("Multiplication = " + c);
            pwrite.println("Multiplication = " + c);
        }
        if (fun.compareTo("div") == 0) {
            c = a / b;
            System.out.println("Division = " + c);
            pwrite.println("Division = " + c);
        }
        System.out.flush();
    }

}