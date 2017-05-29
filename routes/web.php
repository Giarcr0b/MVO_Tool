<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| This file is where you may define all of the routes that are handled
| by your application. Just tell Laravel the URIs it should respond
| to using a Closure or controller method. Build something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', 'HomeController@index');

// Route::post('/portfolios', 'PortfoliosController@store');

/**
 *  Resourceful route for Portfolios
 *
 */
Route::resource('portfolios', 'PortfolioController');

/**
 * Resourceful route for Stocks
 */
Route::resource('stocks', 'StockController');

Route::post('findstocks/{id}', ['uses' => 'StockController@find']);

/**
 * Resourceful route for OPtimisations
 */
Route::resource('optimisations', 'OptimisationController');