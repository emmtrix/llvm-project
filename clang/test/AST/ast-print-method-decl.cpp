// RUN: %clang_cc1 -ast-print %s -o - | FileCheck %s

// CHECK: struct A {
struct A {
  // CHECK-NEXT: A();
  A();

  // CHECK-NEXT: A(int) : A() {
  A(int) : A() {
    // CHECK-NEXT: }
  }


  // CHECK-NEXT: };
};
