var fnGetRows = function(selector){
    var __agComponent = document.querySelector(selector).__agComponent;
    var gridApi = __agComponent.gridOptionsWrapper.getApi();
    var columnApi = __agComponent.gridOptionsWrapper.getColumnApi();

    var ctrls = Array.from(__agComponent.gridOptionsWrapper.gridOptions.api.rowRenderer.getRowCtrls());

    var gridRows = [];

    ctrls.forEach(c => {
        var row = {};

        var left = c.leftCellCtrls.list;
        var center = c.centerCellCtrls.list;

        for(var i = 0; i < left.length; i++)
        {
            row[left[i].column.colId] = left[i];
            row[left[i].column.colDef.headerName] = left[i];
        }

        for(var j = 0; j < center.length; j++)
        {
            row[center[j].column.colId] = center[j];
            row[center[j].column.colDef.headerName] = center[j];
        }

        gridRows.push(row);


    });
    debugger;

    console.log(gridRows);
}
