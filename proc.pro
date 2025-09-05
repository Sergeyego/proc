QT       += core gui sql svg printsupport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(xlsx/qtxlsx.pri)

SOURCES += \
    cfgplot.cpp \
    db/dbcombobox.cpp \
    db/dbdateedit.cpp \
    db/dbdelegate.cpp \
    db/dblogin.cpp \
    db/dbmapper.cpp \
    db/dbrelationeditdialog.cpp \
    db/dbtablemodel.cpp \
    db/dbviewer.cpp \
    db/executor.cpp \
    db/tablemodel.cpp \
    delegate.cpp \
    doublecubewidget.cpp \
    doubleolapmodel.cpp \
    formgraph.cpp \
    formoven.cpp \
    main.cpp \
    mainwindow.cpp \
    modelro.cpp \
    olap/axiswidget.cpp \
    olap/cubewidget.cpp \
    olap/cubic.cpp \
    olap/dialogolapflt.cpp \
    olap/formfilter.cpp \
    olap/olapmodel.cpp \
    olap/tableview.cpp \
    plotdata.cpp \
    qwt/qwt.cpp \
    qwt/qwt_abstract_legend.cpp \
    qwt/qwt_abstract_scale_draw.cpp \
    qwt/qwt_bezier.cpp \
    qwt/qwt_clipper.cpp \
    qwt/qwt_color_map.cpp \
    qwt/qwt_column_symbol.cpp \
    qwt/qwt_curve_fitter.cpp \
    qwt/qwt_date.cpp \
    qwt/qwt_date_scale_draw.cpp \
    qwt/qwt_date_scale_engine.cpp \
    qwt/qwt_dyngrid_layout.cpp \
    qwt/qwt_event_pattern.cpp \
    qwt/qwt_graphic.cpp \
    qwt/qwt_interval.cpp \
    qwt/qwt_interval_symbol.cpp \
    qwt/qwt_legend.cpp \
    qwt/qwt_legend_data.cpp \
    qwt/qwt_legend_label.cpp \
    qwt/qwt_magnifier.cpp \
    qwt/qwt_math.cpp \
    qwt/qwt_matrix_raster_data.cpp \
    qwt/qwt_null_paintdevice.cpp \
    qwt/qwt_painter.cpp \
    qwt/qwt_painter_command.cpp \
    qwt/qwt_panner.cpp \
    qwt/qwt_picker.cpp \
    qwt/qwt_picker_machine.cpp \
    qwt/qwt_pixel_matrix.cpp \
    qwt/qwt_plot.cpp \
    qwt/qwt_plot_abstract_barchart.cpp \
    qwt/qwt_plot_abstract_canvas.cpp \
    qwt/qwt_plot_axis.cpp \
    qwt/qwt_plot_barchart.cpp \
    qwt/qwt_plot_canvas.cpp \
    qwt/qwt_plot_curve.cpp \
    qwt/qwt_plot_dict.cpp \
    qwt/qwt_plot_directpainter.cpp \
    qwt/qwt_plot_graphicitem.cpp \
    qwt/qwt_plot_grid.cpp \
    qwt/qwt_plot_histogram.cpp \
    qwt/qwt_plot_intervalcurve.cpp \
    qwt/qwt_plot_item.cpp \
    qwt/qwt_plot_layout.cpp \
    qwt/qwt_plot_legenditem.cpp \
    qwt/qwt_plot_magnifier.cpp \
    qwt/qwt_plot_marker.cpp \
    qwt/qwt_plot_multi_barchart.cpp \
    qwt/qwt_plot_panner.cpp \
    qwt/qwt_plot_picker.cpp \
    qwt/qwt_plot_rasteritem.cpp \
    qwt/qwt_plot_renderer.cpp \
    qwt/qwt_plot_rescaler.cpp \
    qwt/qwt_plot_scaleitem.cpp \
    qwt/qwt_plot_seriesitem.cpp \
    qwt/qwt_plot_shapeitem.cpp \
    qwt/qwt_plot_spectrocurve.cpp \
    qwt/qwt_plot_spectrogram.cpp \
    qwt/qwt_plot_svgitem.cpp \
    qwt/qwt_plot_textlabel.cpp \
    qwt/qwt_plot_tradingcurve.cpp \
    qwt/qwt_plot_vectorfield.cpp \
    qwt/qwt_plot_zoneitem.cpp \
    qwt/qwt_plot_zoomer.cpp \
    qwt/qwt_point_3d.cpp \
    qwt/qwt_point_data.cpp \
    qwt/qwt_point_mapper.cpp \
    qwt/qwt_point_polar.cpp \
    qwt/qwt_raster_data.cpp \
    qwt/qwt_round_scale_draw.cpp \
    qwt/qwt_sampling_thread.cpp \
    qwt/qwt_scale_div.cpp \
    qwt/qwt_scale_draw.cpp \
    qwt/qwt_scale_engine.cpp \
    qwt/qwt_scale_map.cpp \
    qwt/qwt_scale_widget.cpp \
    qwt/qwt_series_data.cpp \
    qwt/qwt_spline.cpp \
    qwt/qwt_spline_basis.cpp \
    qwt/qwt_spline_cubic.cpp \
    qwt/qwt_spline_curve_fitter.cpp \
    qwt/qwt_spline_local.cpp \
    qwt/qwt_spline_parametrization.cpp \
    qwt/qwt_spline_pleasing.cpp \
    qwt/qwt_spline_polynomial.cpp \
    qwt/qwt_symbol.cpp \
    qwt/qwt_system_clock.cpp \
    qwt/qwt_text.cpp \
    qwt/qwt_text_engine.cpp \
    qwt/qwt_text_label.cpp \
    qwt/qwt_transform.cpp \
    qwt/qwt_vectorfield_symbol.cpp \
    qwt/qwt_weeding_curve_fitter.cpp \
    qwt/qwt_widget_overlay.cpp \
    rels.cpp \
    srcchannel.cpp \
    srcplot.cpp

HEADERS += \
    cfgplot.h \
    db/dbcombobox.h \
    db/dbdateedit.h \
    db/dbdelegate.h \
    db/dblogin.h \
    db/dbmapper.h \
    db/dbrelationeditdialog.h \
    db/dbtablemodel.h \
    db/dbviewer.h \
    db/executor.h \
    db/tablemodel.h \
    delegate.h \
    doublecubewidget.h \
    doubleolapmodel.h \
    formgraph.h \
    formoven.h \
    mainwindow.h \
    modelro.h \
    olap/axiswidget.h \
    olap/cubewidget.h \
    olap/cubic.h \
    olap/dialogolapflt.h \
    olap/formfilter.h \
    olap/olapmodel.h \
    olap/tableview.h \
    plotdata.h \
    qwt/qwt.h \
    qwt/qwt_abstract_legend.h \
    qwt/qwt_abstract_scale_draw.h \
    qwt/qwt_axis.h \
    qwt/qwt_axis_id.h \
    qwt/qwt_bezier.h \
    qwt/qwt_clipper.h \
    qwt/qwt_color_map.h \
    qwt/qwt_column_symbol.h \
    qwt/qwt_curve_fitter.h \
    qwt/qwt_date.h \
    qwt/qwt_date_scale_draw.h \
    qwt/qwt_date_scale_engine.h \
    qwt/qwt_dyngrid_layout.h \
    qwt/qwt_event_pattern.h \
    qwt/qwt_global.h \
    qwt/qwt_graphic.h \
    qwt/qwt_interval.h \
    qwt/qwt_interval_symbol.h \
    qwt/qwt_legend.h \
    qwt/qwt_legend_data.h \
    qwt/qwt_legend_label.h \
    qwt/qwt_magnifier.h \
    qwt/qwt_math.h \
    qwt/qwt_matrix_raster_data.h \
    qwt/qwt_null_paintdevice.h \
    qwt/qwt_painter.h \
    qwt/qwt_painter_command.h \
    qwt/qwt_panner.h \
    qwt/qwt_picker.h \
    qwt/qwt_picker_machine.h \
    qwt/qwt_pixel_matrix.h \
    qwt/qwt_plot.h \
    qwt/qwt_plot_abstract_barchart.h \
    qwt/qwt_plot_abstract_canvas.h \
    qwt/qwt_plot_barchart.h \
    qwt/qwt_plot_canvas.h \
    qwt/qwt_plot_curve.h \
    qwt/qwt_plot_dict.h \
    qwt/qwt_plot_directpainter.h \
    qwt/qwt_plot_graphicitem.h \
    qwt/qwt_plot_grid.h \
    qwt/qwt_plot_histogram.h \
    qwt/qwt_plot_intervalcurve.h \
    qwt/qwt_plot_item.h \
    qwt/qwt_plot_layout.h \
    qwt/qwt_plot_legenditem.h \
    qwt/qwt_plot_magnifier.h \
    qwt/qwt_plot_marker.h \
    qwt/qwt_plot_multi_barchart.h \
    qwt/qwt_plot_panner.h \
    qwt/qwt_plot_picker.h \
    qwt/qwt_plot_rasteritem.h \
    qwt/qwt_plot_renderer.h \
    qwt/qwt_plot_rescaler.h \
    qwt/qwt_plot_scaleitem.h \
    qwt/qwt_plot_seriesitem.h \
    qwt/qwt_plot_shapeitem.h \
    qwt/qwt_plot_spectrocurve.h \
    qwt/qwt_plot_spectrogram.h \
    qwt/qwt_plot_svgitem.h \
    qwt/qwt_plot_textlabel.h \
    qwt/qwt_plot_tradingcurve.h \
    qwt/qwt_plot_vectorfield.h \
    qwt/qwt_plot_zoneitem.h \
    qwt/qwt_plot_zoomer.h \
    qwt/qwt_point_3d.h \
    qwt/qwt_point_data.h \
    qwt/qwt_point_mapper.h \
    qwt/qwt_point_polar.h \
    qwt/qwt_raster_data.h \
    qwt/qwt_round_scale_draw.h \
    qwt/qwt_samples.h \
    qwt/qwt_sampling_thread.h \
    qwt/qwt_scale_div.h \
    qwt/qwt_scale_draw.h \
    qwt/qwt_scale_engine.h \
    qwt/qwt_scale_map.h \
    qwt/qwt_scale_widget.h \
    qwt/qwt_series_data.h \
    qwt/qwt_series_store.h \
    qwt/qwt_spline.h \
    qwt/qwt_spline_basis.h \
    qwt/qwt_spline_cubic.h \
    qwt/qwt_spline_curve_fitter.h \
    qwt/qwt_spline_local.h \
    qwt/qwt_spline_parametrization.h \
    qwt/qwt_spline_pleasing.h \
    qwt/qwt_spline_polynomial.h \
    qwt/qwt_symbol.h \
    qwt/qwt_system_clock.h \
    qwt/qwt_text.h \
    qwt/qwt_text_engine.h \
    qwt/qwt_text_label.h \
    qwt/qwt_transform.h \
    qwt/qwt_vectorfield_symbol.h \
    qwt/qwt_weeding_curve_fitter.h \
    qwt/qwt_widget_overlay.h \
    rels.h \
    srcchannel.h \
    srcplot.h

FORMS += \
    cfgplot.ui \
    db/dblogin.ui \
    db/dbrelationeditdialog.ui \
    formgraph.ui \
    formoven.ui \
    mainwindow.ui \
    olap/axiswidget.ui \
    olap/cubewidget.ui \
    olap/dialogolapflt.ui \
    olap/formfilter.ui

win32:RC_FILE = ico.rc
macx:ICON = ico.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ico.rc

RESOURCES += \
    res.qrc
