import QtQuick 2.0

treeView {
    style: TreeViewStyle {
        branchDelegate: Rectangle {
            width: 15; height: 15;
            color: styleData.isExpanded ? "red" : "green";
        }
    }
}
