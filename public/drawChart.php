<?php

class DrawChart
{
    public $return;
    public $risk;

    public function _construct($return, $risk)
    {


        include('pChart2.1.4/class/pDraw.class.php');
        include('pChart2.1.4/class/pImage.class.php');
        include('pChart2.1.4/class/pData.class.php');
        include('pChart2.1.4/class/pScatter.class.php');

        /* Create and populate the pData object */
        $frontierData = new pData();
        /* x axis */
        $frontierData->addPoints($risk, "Risk");
        $frontierData->setAxisName(0, "Risk");
        $frontierData->setAxisXY(0, AXIS_X);
        $frontierData->setAxisPosition(0, AXIS_POSITION_BOTTOM);

        /* y axiz */
        $frontierData->addPoints($return, "Return");
        $frontierData->setSerieOnAxis("Return", 1);
        $frontierData->setAxisName(1, "Return");
        $frontierData->setAxisXY(1, AXIS_Y);

        /* Set scatter line series */
        $frontierData->setScatterSerie("Risk", "Return", 0);
        $frontierData->setScatterSerieDescription(0, "Efficiency frontier");
        $frontierData->setScatterSerieColor(0, array("R" => 0, "G" => 0, "B" => 0));

        /* Create the pChart object */
        $frontierPicture = new pImage(800, 600, $frontierData);

        /* Overlay with a gradient */
        $Settings = array("StartR" => 50, "StartG" => 50, "StartB" => 170, "EndR" => 100, "EndG" => 100, "EndB" => 250, "Alpha" => 70);
        $frontierPicture->drawGradientArea(0, 0, 800, 600, DIRECTION_VERTICAL, $Settings);
        $frontierPicture->drawGradientArea(0, 0, 800, 30, DIRECTION_VERTICAL, array("StartR" => 20, "StartG" => 20, "StartB" => 100, "EndR" => 70, "EndG" => 70, "EndB" => 250, "Alpha" => 80));

        /* Add a border to the picture */
        $frontierPicture->drawRectangle(0, 0, 799, 599, array("R" => 0, "G" => 0, "B" => 0));

        /* Write the picture title */
        $frontierPicture->setFontProperties(array("FontName" => "pChart2.1.4/fonts/GeosansLight.ttf", "FontSize" => 14));
        $frontierPicture->drawText(10, 25, "Portfolio: Title", array("R" => 255, "G" => 255, "B" => 255));

        /* Write the chart title */
        $frontierPicture->setFontProperties(array("FontName" => "pChart2.1.4/fonts/GeosansLight.ttf", "FontSize" => 14));
        $frontierPicture->drawText(180, 70, "Efficiency Frontier", array("FontSize" => 24, "Align" => TEXT_ALIGN_BOTTOMMIDDLE));

        /* Draw the scale and the 1st chart */
        $frontierPicture->setGraphArea(60, 80, 760, 500);
        $frontierPicture->drawFilledRectangle(60, 80, 760, 500, array("R" => 255, "G" => 255, "B" => 255, "Surrounding" => -200, "Alpha" => 10));
        $frontierPicture->setShadow(TRUE, array("X" => 1, "Y" => 1, "R" => 0, "G" => 0, "B" => 0, "Alpha" => 10));
        $frontierPicture->setFontProperties(array("FontName" => "pChart2.1.4/fonts/GeosansLight.ttf", "FontSize" => 14));

        /* Draw Scatter */
        $frontierScatter = new pScatter($frontierPicture, $frontierData);
        $frontierScatter->drawScatterScale();
        $frontierScatter->drawScatterPlotChart();

        /* Write the chart legend */
        $frontierScatter->drawScatterLegend(50, 550, array("Style" => LEGEND_NOBORDER, "Mode" => LEGEND_HORIZONTAL));

        /* Render the picture (choose the best way) */
        $this->chart = $frontierPicture->autoOutput("pictures/example.drawScatterPlotChart.png");
    }
}