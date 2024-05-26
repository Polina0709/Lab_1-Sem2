//
//  UnitTest.m
//  UnitTest
//
//  Created by Polya Melnik on 26.05.2024.
//

#import <XCTest/XCTest.h>
#import "SplayTree.h"

@interface UnitTest : XCTestCase

@end

@implementation UnitTest

- (void)testInsert {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    XCTAssertEqual(tree.search("Alice"), 1);
    XCTAssertEqual(tree.search("Bob"), 2);
    XCTAssertEqual(tree.search("Charlie"), 3);
}

- (void)testSearch {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    XCTAssertEqual(tree.search("Bob"), 2);
    XCTAssertEqual(tree.search("David"), -1);
    XCTAssertEqual(tree.search("Alice"), 1);
}

- (void)testRemoveExistingElement {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    tree.remove("Bob");
    
    XCTAssertEqual(tree.search("Bob"), -1);
}

- (void)testRemoveNonExistingElement {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    tree.remove("David");
    
    XCTAssertEqual(tree.search("David"), -1);
}

- (void)testRemoveFromEmptyTree {
    SplayTree tree;
    
    tree.remove("Alice");
    
    XCTAssertEqual(tree.search("Alice"), -1);
}

- (void)testPrintTree {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    NSString *expectedOutput = @"Alice (1) Bob (2) Charlie (3) ";
    
    std::string result = tree.printInOrder();
    XCTAssertEqualObjects(@(result.c_str()), expectedOutput);
}

- (void)testSearchByIdentifier {
    SplayTree tree;
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    
    std::string result1 = tree.searchByIdentifier(2);
    std::string result2 = tree.searchByIdentifier(4);
    
    XCTAssertEqualObjects(@(result1.c_str()), @"Bob");
    XCTAssertEqualObjects(@(result2.c_str()), @"");
}



@end
